#include "include/mongoose.h"
#include "pqxx/pqxx"
#include <iostream>
#include <string>

namespace util {

std::string getenv(const std::string &name, const std::string &default_value) {
  const char *value{std::getenv(name.c_str())};
  if (value == nullptr) {
    return default_value;
  } else {
    return value;
  }
}

} // namespace util

int main() {
  try {
    struct mg_mgr mgr {};
    mg_mgr_init(&mgr);

    mg_http_listen(
        &mgr, "http://0.0.0.0:5000",
        [](struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
          if (ev == MG_EV_HTTP_MSG) {
            struct mg_http_message *hm = (struct mg_http_message *)ev_data;

            std::cout << hm->message.ptr << "\n"; // Log requests

            const std::string content_type{"Content-Type:text/html\r\n"};

            if (mg_http_match_uri(hm, "/")) {
              mg_http_reply(c, 200, content_type.c_str(), "%s",
                            "<a href=\"/postgres\">Visit me</a>");
            } else if (mg_http_match_uri(hm, "/postgres")) {
              try {
                // Should allow easier manual running of the server when we
                // don't set environment variables.
                const std::string conn_user{
                    "user=" + util::getenv("POSTGRES_USER", "admin")};
                const std::string conn_password{
                    "password=" + util::getenv("POSTGRES_PASSWORD", "admin")};
                const std::string conn_dbname{
                    "dbname=" + util::getenv("POSTGRES_DB", "db")};
                const std::string conn_str{conn_user + " " + conn_password +
                                           " " + conn_dbname +
                                           " host=postgres port=5432"};
                pqxx::connection conn{conn_str};

                if (conn.is_open()) {
                  std::cout << "Connected to PostgreSQL database.\n";
                } else {
                  throw std::runtime_error{
                      "Failed to connect to PostgreSQL database."};
                }

                pqxx::work txn{conn};
                pqxx::result result{txn.exec("SELECT * FROM my_schema.users")};

                auto create_user_lists{[&result]() {
                  std::string lists;
                  for (const auto &row : result) {
                    lists += "<ul>";
                    for (const auto &field : row) {
                      lists += "<li>";
                      lists += field.name();
                      lists += " : ";
                      lists += field.c_str();
                      lists += +"</li>";
                    }
                    lists += "</ul>";
                  }
                  return lists;
                }};

                std::string response{R"(
                  <!DOCTYPE html>
                  <html>
                    <head>
                      <title>Poorly written server</title>
                    </head>
                    <body>
                      <h1>Hello poorly written server</h1>
                      )" + create_user_lists() +
                                     R"(
                    </body>
                  </html>
                )"};

                mg_http_reply(c, 200, content_type.c_str(), "%s",
                              response.c_str());
                txn.commit();
                conn.disconnect();
              } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
                mg_http_reply(c, 500, content_type.c_str(), "%s",
                              "Internal server error.\n");
              }
            } else {
              mg_http_reply(c, 200, content_type.c_str(), "%s",
                            "Unsupported URI.\n");
            }
          }
        },
        nullptr);

    std::cout << "Server on: http://localhost:5000/\n";

    while (true) {
      mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
