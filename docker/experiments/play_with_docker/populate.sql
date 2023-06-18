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
