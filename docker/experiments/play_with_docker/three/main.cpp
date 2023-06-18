#include "pqxx/pqxx"
#include <iostream>
#include <string>

int main() {
  try {
    pqxx::connection conn(
        "dbname=db user=admin password=admin host=postgres port=5432");

    if (conn.is_open()) {
      std::cout << "Connected to PostgreSQL database.\n";
    } else {
      throw std::runtime_error{"Failed to connect to PostgreSQL database."};
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

    std::cout << response << "\n";
    txn.commit();

    conn.disconnect();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
