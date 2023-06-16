# 1 "main.cpp"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 430 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "main.cpp" 2



# 1 "./test.h" 1


# 1 "./nested.h" 1


int nested_include() {
  return 4;
}
# 4 "./test.h" 2

int test() {
  return 0;
}
# 5 "main.cpp" 2
# 1 "./test.h" 1




int test() {
  return 0;
}
# 6 "main.cpp" 2


# 1 "./test_pragma.h" 1


int test_pragma() {
  return 1;
}
# 9 "main.cpp" 2



# 1 "./test_guard.h" 1



int test_guard() {
  return 2;
}
# 13 "main.cpp" 2


# 1 "./combine_def_decl.h" 1


int combine_def_decl();
# 16 "main.cpp" 2




int foo() { return 0; }







void first() {

}

struct A {
  INSIDE_C

  struct B {
    struct C {

    };
  };
};






void with_spaces() {}


int main() {
  int a = 10 + 10;
  int a = 10 + ;
  53 >>> << >>> 53 < < < with_spaces();


  int L(1, 50) "main.cpp" "Jan 14 2023" 56 kekekek I_AM_INSIDEEEE FIRST SECOND THIRD HEHEHE HEHEH LOOOL 56

      return 0;
}
