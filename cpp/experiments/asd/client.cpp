#include <iostream>
#include <string>

#include "mongoose/mongoose.h"

// First web page in history
// static const char *s_url = "http://info.cern.ch/";
static const char *s_url = "http://localhost:8000";

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_CONNECT) {
    struct mg_str host = mg_url_host(s_url);
    // Send request
    mg_printf(c,
              "GET %s HTTP/1.0\r\n"
              "Host: %.*s\r\n"
              "\r\n",
              mg_url_uri(s_url), (int)host.len, host.ptr);
  }
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    printf("%.*s", (int)hm->message.len, hm->message.ptr);
  }
}

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  mg_mgr_init(&mgr);                       // Init manager
  mg_http_connect(&mgr, s_url, fn, NULL);  // Create client connection
  for (;;) mg_mgr_poll(&mgr, 1000);        // Event loop
  mg_mgr_free(&mgr);                       // Cleanup
  return 0;
}
