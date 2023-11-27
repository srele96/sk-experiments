cmake_minimum_required(VERSION 3.20)

project(algorithms)

add_executable(
  ${PROJECT_NAME}
  test/main.cpp
)

enable_testing()

find_package(GTest CONFIG REQUIRED)

target_link_libraries(
  ${PROJECT_NAME}

  PRIVATE

  GTest::gtest_main
  GTest::gtest
  GTest::gmock_main
  GTest::gmock
)
