#include "whatever.h"

#include <string>

int whatever::give_me_int() {
  const int whatever_number{42};

  return whatever_number;
}

std::string whatever::give_me_string() {
  std::string whatever_string{"whatever"};

  return whatever_string;
}
