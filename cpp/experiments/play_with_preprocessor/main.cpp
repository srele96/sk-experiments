#pragma once

// include twice
#include "test.h"
#include "test.h"

// include twice
#include "test_pragma.h"
#include "test_pragma.h"

// include twice
#include "test_guard.h"
#include "test_guard.h"

#ifndef __WTF__
#define __TEST__

int foo() { return 0; }

#endif

#define WOAH

#define TEST 10

void first() {

}

struct A {
  // does it get replaced? no, it is defined after
  INSIDE_C

  struct B {

    struct C {
      // can i place define inside nested struct?
      #define INSIDE_C I_AM_INSIDEEEE
    };

  };
};

// does it take content with spaces?
#define WITH_SPACES FIRST SECOND THIRD HEHEHE HEHEH LOOOL __LINE__

// how does define without string behave
#define test

// does this check for truthiness?
#ifdef test
void with_spaces() {}
#endif  // WITH_SPACES

int main() {
  // does it get replaced?
  int a = 10 + TEST;
  // does it get replaced?
  int a = 10 + WOAH;
  __LINE__ >>> WOAH << >>> __LINE__ < < < with_spaces();

// can i place define inside main? somewhere else?
#define __LOL kekekek

  int L(1, 50) __FILE__ __DATE__ __LINE__ __LOL INSIDE_C WITH_SPACES

      return 0;
}
