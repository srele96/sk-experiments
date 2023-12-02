#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

int add(int i, int j) { return i + j; }

void process_data(int data) {
  constexpr int seconds{1};
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  data *= 2;
}

std::vector<int> threaded_operation(std::vector<int> data) {
  std::vector<std::thread> threads;

  for (int& value : data) {
    threads.emplace_back(process_data, std::ref(value));
  }

  for (auto& thread : threads) {
    thread.join();
  }

  return data;
}

void each_async(std::vector<int> data, std::function<void(int)> callback) {
  for (const int value : data) {
    constexpr int one{1};
    std::this_thread::sleep_for(std::chrono::seconds(one));

    constexpr int magnifier{2};
    callback(value * magnifier);
  }
}

void use_object(const pybind11::object& object) {
  std::cout << "object: " << pybind11::str(object) << "\n";
}

PYBIND11_MODULE(example, m) {
  m.def("add", &add);
  m.def("threaded_operation", &threaded_operation);
  m.def("each_async", &each_async);
  m.def("use_object", &use_object);
}
