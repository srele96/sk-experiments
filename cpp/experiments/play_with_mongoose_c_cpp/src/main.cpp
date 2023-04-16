#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "mongoose/mongoose.h"

struct state {
  std::string m_whatever;
};

int main(const int argc, const char* argv[]) {
  struct mg_mgr mgr {};
  const std::string m_whatever{"initial value"};
  state _state{m_whatever};

  mg_log_set(MG_LL_DEBUG);
  mg_mgr_init(&mgr);
  const std::string url{"http://0.0.0.0:8000"};

  mg_http_listen(
      &mgr, url.c_str(),
      [](struct mg_connection* connection, int event, void* event_data,
         void* function_data) {
        state* _state = static_cast<state*>(function_data);

        // Every connection is here...
        // I see... event data is different for each event, hence it is
        // pointer to void which means it can be casted to the type of data we
        // want fn_data is also of type any because we receive multiple events
        // here and it's is different for different events. therefore fn_data
        // and ev_data are generic types which depend on the event
        switch (event) {
          case MG_EV_HTTP_MSG: {
            // The code from the example puts the code in here.
            // runs after http_chunk, why?
            // print connection information, is it shared across all events?
            // what about parallel connections?
            //
            // event data is struct mg_http_message*

            // write one chunk of response
            // send back json response
            // print connection buffer or wherever mg_http_reply writes to

            // NOTE
            // - how to pass lambda to c function pointer when it has capture
            // list
            // Alternatively, find another way to send delayed chunk response.
            //  ----------------------------------------------------------------
            //  Note
            //  Send chunk one by one for each poll event to see whether it
            //  gets appended to the client. So far, when the chunk is sent,
            //  it is visible in the client. If the last chunk is not empty,
            //  then the client is waiting and connection is not closed.
            //  Therefore we may have hope to see how to transfer data from
            //  the server to the client while the connection is open and the
            //  client has the opportunity to work with the data as it is
            //  received. That will be cool because after thinking about it
            //  ever since I left the house today I wanted to do it. I wanted
            //  to see how can I use the connection while it is open to
            //  exchange data in the real time.
            //  ----------------------------------------------------------------

            std::cout << "Received http message...\n";

            break;
          }
          case MG_EV_HTTP_CHUNK: {
            // print connection information, received before http_msg, why?
            // event data is struct mg_http_message*

            struct mg_http_message* request{
                static_cast<struct mg_http_message*>(event_data)};

            std::string line_break{
                "--------------------------------------------------"};
            std::cout << "Chunk:\n"
                      << line_break << "\n\n"
                      << request->head.ptr << "\n"
                      << line_break << request->chunk.ptr << "\n"
                      << line_break << "\n\n";
            break;
          }
          case MG_EV_POLL: {
            break;
          }
          default: {
            break;
          }
        }
      },
      &_state);

  while (true) {
    // Make sure the server polls extremely fast
    constexpr int interval{1000};
    mg_mgr_poll(&mgr, interval);
  }

  mg_mgr_free(&mgr);

  return 0;
}
