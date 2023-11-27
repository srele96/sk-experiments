add_executable(
  ${PROJECT_NAME}

  ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}

  PRIVATE
  # The library must be built manually. If there are any build errors, check
  # .\BuildMongooseLib.bat and .\BuildMongooseLib.ps1
  ${PROJECT_SOURCE_DIR}/include/mongoose/lib/mongoose.lib
  # The `mongoose` library depends on `ws2_32.lib` which is the windows socket
  # library.
  ws2_32.lib
)

target_include_directories(
  ${PROJECT_NAME}

  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
