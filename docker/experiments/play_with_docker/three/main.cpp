#include "include/httplib.h"
#include "pqxx/pqxx"
#include <functional>
#include <iostream>
#include <string>
#include <utility>

int main() {
  try {
    pqxx::connection conn(
        "dbname=db user=admin password=admin host=localhost port=5432");

    if (conn.is_open()) {
      std::cout << "Connected to PostgreSQL database." << std::endl;
    } else {
      throw std::runtime_error{"Failed to connect to PostgreSQL database."};
    }

    pqxx::work txn_one{conn};
    std::cout << "Creating schema my_schema.\n";
    txn_one.exec("CREATE SCHEMA IF NOT EXISTS my_schema");

    std::cout << "Successfully created schema my_schema.\nCreating users "
                 "table.\n";
    txn_one.exec(R"(
      CREATE TABLE IF NOT EXISTS my_schema.users (
        id SERIAL PRIMARY KEY,
        username VARCHAR(50) NOT NULL UNIQUE,
        first_name VARCHAR(50) NOT NULL,
        last_name VARCHAR(50) NOT NULL,
        email VARCHAR(100) NOT NULL,
        phone_number VARCHAR(20)
      );
    )");
    std::cout << "Successfully created users table.\nCreating user data\n";

    txn_one.exec(R"(
      INSERT INTO my_schema.users (username, first_name, last_name, email, phone_number)
      SELECT 'john_doe', 'John', 'Doe', 'john@example.com', '1234567890'
      WHERE NOT EXISTS (
        SELECT 1 FROM my_schema.users WHERE username = 'john_doe'
      );

      INSERT INTO my_schema.users (username, first_name, last_name, email, phone_number)
      SELECT 'jane_smith', 'Jane', 'Smith', 'jane@example.com', NULL
      WHERE NOT EXISTS (
        SELECT 1 FROM my_schema.users WHERE username = 'jane_smith'
      );
    )");
    std::cout << "Successfully created user data.\n";

    txn_one.commit();

    httplib::Server server;

    server.Get("/postgres",
               [&conn](const httplib::Request &, httplib::Response &res) {
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
    )" + create_user_lists() + R"(
  </body>
</html>
          )"};

                 res.status = 200;
                 res.set_content(response, "text/html");
                 txn.commit();
               });

    std::cout << "Server on http://localhost:5000\n";
    server.listen("localhost", 5000);
    conn.disconnect();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
