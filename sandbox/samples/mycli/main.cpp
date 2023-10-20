#include "boost/program_options.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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

auto main(int argc, char **argv) -> int {
  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()("help, h", "Help me to use `mycli`!")
      // TODO: Learn the pattern to construct<type>()
      ("file, f", po::value<std::string>(),
       "Do stuff with a file on this path.")("db-test",
                                             "Test the database connection.");

  po::variables_map v_map;

  try {
    po::store(po::parse_command_line(argc, argv, desc), v_map);
    po::notify(v_map);

    if (v_map.count("help") != 0 || argc == 1) {
      std::cout << desc << "\n";
    }

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

  } catch (const po::error &exception) {
    std::cerr << exception.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
