#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "mongoose/mongoose.h"

class state {
 public:
  std::string m_whatever{"initial value"};
};

int main(const int argc, const char* argv[]) {
  struct mg_mgr mgr {};
  state _state;

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

            // mg_printf(connection, "%s",
            //           "HTTP/1.0 200 OK\r\n"
            //           "Content-Type: text/html\r\n"
            //           "Content-Length: 5\r\n"
            //           "\r\n");
            // mg_send(connection, "hello", 5);
            // mg_send(connection, "\r\n", 2);

            mg_printf(connection, "%s",
                      "HTTP/1.1 200 OK\r\n"
                      "Transfer-Encoding: chunked\r\n"
                      "Access-Control-Allow-Origin: *\r\n"
                      "Content-Type: text/plain\r\n"
                      "\r\n");
            // mg_http_printf_chunk(connection, "%s", "first");
            // mg_http_printf_chunk(connection, "%s", "second");
            // mg_http_printf_chunk(connection, "%s", "third");
            // mg_http_printf_chunk(connection, "%s", "fourth");

            // validates that they run in parallel or sequential
            std::cout << "\n\n\n\n\nStarting...\n\n\n";

            // validate that the client receives data in real time
            for (int i{0}; i != 10000; ++i) {
              // slow down the loop to make sure it runs longer than the server
              // polls print url of connection
              std::cout << "send...";
              mg_http_printf_chunk(connection, "%s", "hello -> ");
            }

            mg_http_printf_chunk(connection, "");

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

            break;
          }
          case MG_EV_HTTP_CHUNK: {
            // print connection information, received before http_msg, why?
            // event data is struct mg_http_message*

            break;
          }
          case MG_EV_POLL: {
            std::cout << "Poll\n";
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
    constexpr int interval{1};
    mg_mgr_poll(&mgr, interval);
  }

  mg_mgr_free(&mgr);

  return 0;
}
