#include "pqxx/pqxx"
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

    pqxx::work txn_two{conn};

    for (const auto &row : txn_two.exec("SELECT * FROM my_schema.users")) {
      for (const auto &column : row) {
        if (!column.is_null()) {
          std::cout << column.as<std::string>() << " ";
        }
      }
      std::cout << "\n";
    }

    txn_two.commit();

    conn.disconnect();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
