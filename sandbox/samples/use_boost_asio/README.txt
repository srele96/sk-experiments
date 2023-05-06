# Use boost::asio

Use boost::asio to verify that it works with the sandbox and vcpkg setup.

## Original intentions

I originally wanted to use boost::asio to write to a file asynchronously, but
later thought that I am not sure whether that makes sense... I didn't even
have well defined behavior requirements.

I ended up using boost::asio code from tutorial for asynchronous timer. That
validated that boost::asio works with the sandbox and vcpkg setup.

## Some of the things I tried

### Define the problem

boost windows stream requires a file handle, to create a file handle we have to
call windows function CreateFile, that function takes parameters where each
parameter represents some functionality which i did not consider before, hence
i have to consider each of them back in the problem statement and figure out
how to solve the problem again, so i have to jump between finding out new
information, adding it back to the problem statement, going back to attempt to
solve the problem, finding out a new statement that should go back to the
problem statement, solving the problem statement again, running back and forth
until i solve the problem, add relevant tests, etc...

that technique resembles the way algorithmic problems are solved, you can't
type some code and pray it solves the problem, solution translated into code
like that almost never works correctly...

### Create a file handle

Boost asio works with `boost::asio::windows::stream_handle` which takes
`boost::asio::io_context` and a `HANDLE`. I found that I can create it using
windows api `CreateFile`. Then I added it back in the problem statement. After
that I read documentation to figure out what behavior there is and what
behavior do I want.

CreateFile
  success (state)
  error (state)

See more on CreateFile:
  https://learn.microsoft.com/en-us/windows/win32/fileio/creating--deleting--and-maintaining-files
  https://learn.microsoft.com/en-us/windows/win32/fileio/creating-and-opening-files
  https://learn.microsoft.com/en-us/windows/win32/fileio/closing-and-deleting-files

- What do i need to do?
  - i need the most basic functionality when opening a file

  - I need to open file only for writing
  - Free the handle when it's not in use any more
- Which parameters do i need and why?

create file handle in mode to open file if it exist and create if it doesn't

See parameters:
https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea

lpFileName
  "resource_one.txt"
dwDesiredAccess
  // I wanted to read and write.
  GENERIC_READ | GENERIC_WRITE
dwShareMode
  // Prevent undesired effects by other processes.
  0
lpSecurityAttributes
  // I didn't need anything that I was aware of.
  NULL
dwCreationDisposition
  // Create if doesn't exist, open if exist.
  OPEN_ALWAYS
dwFlagsAndAttributes
  // There was runtime error without this flag.
  FILE_FLAG_OVERLAPPED
hTemplateFile
  // I didn't need one.
  NULL

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Attempts to get it working

## First attempt to get it working.

Code in progress, i dislike committing code that's not a logical whole

```cpp
/**
 * Note!
 *
 * I didn't work with files using C++ and boost::asio before. Therefore I am not
 * aware of some of the best practices so I'm not sure if everything I've done
 * is done correctly.
 **/
#include "boost/asio.hpp"
#include <fileapi.h>
#include <iostream>

int main() {
  try {
    boost::asio::io_context io_context;
    boost::asio::io_context::strand strand{io_context};
    // See parameters:
    // https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
    //
    // I just chose whichever worked, here is why two functions can create a
    // file handle:
    // https://stackoverflow.com/questions/51462048/what-is-the-difference-between-createfile-and-createfilea
    HANDLE file_handle{CreateFileA(
        "resource_one.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
        FILE_FLAG_OVERLAPPED // Enable asynchronous operations because
                             // boost::asio::windows::stream_handle uses
                             // overlapped_stream_handle
                             // https://www.reddit.com/r/cpp_questions/comments/x28y0a/boostasiowindowsstream_handle_error_assign_the/
        ,
        NULL)};
    if (file_handle == INVALID_HANDLE_VALUE) {
      throw std::runtime_error("Failed to create file handle");
    }
    boost::asio::windows::stream_handle handle{io_context, file_handle};

    handle.async_write_some(
        boost::asio::buffer("Hello world"),
        [&handle](const boost::system::error_code &ec, std::size_t bytes) {
          if (ec) {
            std::cerr << "Error: " << ec.message() << "\n";
          } else {
            std::cout << "Wrote " << bytes << " bytes"
                      << "\n";
          }
        });
    handle.async_write_some(
        boost::asio::buffer("WoW! Much async!"),
        [](const boost::system::error_code &ec, std::size_t bytes) {
          if (ec) {
            std::cerr << "Error: " << ec.message() << "\n";
          } else {
            std::cout << "Wrote " << bytes << " bytes"
                      << "\n";
          }
        });

    constexpr int MAX_BUFFER_SIZE {1024};
    char buffer[MAX_BUFFER_SIZE];

    io_context.run();
    CloseHandle(file_handle);
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
```

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

### The second attempt to get it working.

```cpp
#include "boost/asio.hpp"
#include "boost/system.hpp"
#include <fileapi.h>
#include <iostream>

int main() {
  try {
    boost::asio::io_context io_context;

    HANDLE h_file{CreateFileA("resource_one.txt", GENERIC_READ | GENERIC_WRITE,
                              0, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED,
                              NULL)};
    if (h_file == INVALID_HANDLE_VALUE) {
      throw std::runtime_error("Failed to open file");
    }

    boost::asio::windows::stream_handle stream_handle{io_context, h_file};

    auto notify_on_done{
        [](const boost::system::error_code &ec, std::size_t bytes_transferred) {
          if (ec) {
            std::cout << "Error occured! Error code = " << ec.value()
                      << ". Message: " << ec.message() << "\n";
            return;
          }
          std::cout << "Bytes transferred: " << bytes_transferred << "\n";
          // One thing I could do is setup another asynchronous operatio here.
        }};
    std::cout << "Before calls to async writes.\n";
    stream_handle.async_write_some(
        boost::asio::buffer("Asynch! First write, it works!"), notify_on_done);
    stream_handle.async_write_some(
        boost::asio::buffer("WoW! Much async, second write!"), notify_on_done);
    stream_handle.async_write_some(
        boost::asio::buffer("Third round! What happens now?"), notify_on_done);
    std::cout << "After calls to async writes.\n";

    io_context.run();
    CloseHandle(h_file);
  } catch (std::exception &e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}
```
