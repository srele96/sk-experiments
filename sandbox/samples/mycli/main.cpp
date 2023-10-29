#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "boost/program_options.hpp"
#include "bsoncxx/json.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/exception/exception.hpp"
#include "mongocxx/instance.hpp"
#include "mongocxx/uri.hpp"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Self Note:
//
// These concepts are not difficult or challenging at all.
// I should be ramping up the difficulty to increase my skill.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// TODO: Write unit tests for this...

namespace mycli {

const char DATE_DELIMITER{':'};

struct date {
  std::string year;
  std::string month;
  std::string day;

  friend auto operator>>(std::istream &istream, date &p_date) -> std::istream &;
  friend auto operator<<(std::ostream &ostream, const date &p_date)
      -> std::ostream &;
};

auto operator>>(std::istream &istream, date &p_date) -> std::istream & {
  // Ignore erroneous logic and missed cases. This sample only practices the
  // custom types in boost::program_options.

  if (!std::getline(istream, p_date.year, DATE_DELIMITER)) {
    throw std::runtime_error("Failed to read the year.");
  }
  if (!std::getline(istream, p_date.month, DATE_DELIMITER)) {
    throw std::runtime_error("Failed to read the month.");
  }
  if (!std::getline(istream, p_date.day)) {
    throw std::runtime_error("Failed to read the day.");
  }

  // Leave logging because boost repeatedly printed error:
  // the argument ('1111:11:32') for option '--date' is invalid
  // In the end I made it work using three if statements.
  //
  // I greedily read from the stream. Last std::getline read the year of the
  // next date and triggered the error.
  if (istream.eof()) {
    std::cout << "End of file reached.\n";
  } else if (istream.fail()) {
    std::cout << "Failed to read the date.\n";
  } else if (istream.bad()) {
    std::cout << "Bad stream.\n";
  }

  return istream;
}

auto operator<<(std::ostream &ostream, const date &p_date) -> std::ostream & {
  ostream << p_date.year << DATE_DELIMITER << p_date.month << DATE_DELIMITER
          << p_date.day;

  return ostream;
}

} // namespace mycli

auto main(int argc, char **argv) -> int {
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
      /**/
      ("help, h", "Help me to use `mycli`!")
      /*
       * TODO: Learn the pattern to construct<type>()
       */
      ("file, f", po::value<std::string>(),
       "Do stuff with a file on this path.")
      /**/
      ("db-test", "Test the database connection.")
      /**/
      ("date", po::value<mycli::date>(),
       "Print the user provided date in the format YYYY-MM-DD")
      /**/
      ("dates", po::value<std::vector<mycli::date>>(),
       "Print the user provided dates in the format YYYY-MM-DD.");

  po::variables_map v_map;

  // Parse args and run the logic for each provided option.
  try {
    po::store(po::parse_command_line(argc, argv, desc), v_map);
    po::notify(v_map);

    if (v_map.count("help") != 0 || argc == 1) {
      std::cout << desc << "\n";
    }

    // Print the file information.
    if (v_map.count("file") != 0) {
      const std::string filename{v_map["file"].as<std::string>()};
      // TODO: Disable red underline
      const std::filesystem::path absolute_path{
          std::filesystem::absolute(filename)};
      std::ifstream file{absolute_path};

      if (file.is_open()) {
        std::cout << "Processing file: " << absolute_path << "\n";

        std::string line;
        std::vector<std::string> words;
        std::string content;

        while (std::getline(file, line)) {
          content += line + "\n";

          std::ifstream line_stream{line};
          std::string word;

          while (line_stream >> word) {
            words.push_back(word);
          }
        }

        std::cout << "The file contains " << words.size() << " words.\n";
        std::cout << "The content of the file is:\n```"
                  << absolute_path.extension().string() << "\n"
                  << content << "\n```\n";

        file.close();
      } else {
        std::cerr << "Unable to open file: " << absolute_path << "\n";
      }
    }

    // Connect, create, read and notify the user on success or failure.
    if (v_map.count("db-test") != 0) {
      auto test_connection{[](const std::string &label) {
        return "Test database connection -- " + label + "\n";
      }};

      std::cout << test_connection("BEGIN");

      try {
        mongocxx::instance instance;
        // We're embedding secrets in the code. Not cool.
        mongocxx::uri uri{"mongodb://admin:admin@localhost:27017"};
        mongocxx::client client{uri};

        mongocxx::collection users{client["myclidb"]["users"]};

        if (users.count_documents({}) > 0) {
          std::cout << "First 5 documents in the collection users:\n";
          for (auto &&doc :
               users.find({}, mongocxx::options::find{}.limit(5))) {
            std::cout << bsoncxx::to_json(doc) << "\n";
          }
        } else {
          std::cout << "No documents found in the collection users.\n";
        }

        mongocxx::collection not_exist{client["myclidb"]["not_exist"]};

        if (not_exist.count_documents({}) > 0) {
          std::cout << "First 5 documents in the collection not_exist:\n";
          for (auto &&doc :
               not_exist.find({}, mongocxx::options::find{}.limit(5))) {
            std::cout << bsoncxx::to_json(doc) << "\n";
          }
        } else {
          std::cout << "No documents found in the collection not_exist.\n";
        }
      } catch (const mongocxx::exception &exception) {
        std::cerr << exception.what() << "\n";
      }

      std::cout << test_connection("END");
    }

    if (v_map.count("date") != 0) {
      const mycli::date date{v_map["date"].as<mycli::date>()};

      std::cout << "Date: " << date << "\n";
    }

    if (v_map.count("dates") != 0) {
      const std::vector<mycli::date> dates{
          v_map["dates"].as<std::vector<mycli::date>>()};

      std::cout << "Dates: ";
      for (const auto &date : dates) {
        std::cout << date << " ";
      }
      std::cout << "\n";
    }
  } catch (const po::error &exception) {
    std::cerr << exception.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
