CREATE SCHEMA IF NOT EXISTS my_schema;

CREATE TABLE IF NOT EXISTS my_schema.users (
  id SERIAL PRIMARY KEY,
  username VARCHAR(50) NOT NULL,
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50) NOT NULL,
  email VARCHAR(100) NOT NULL,
  phone_number VARCHAR(20)
);
