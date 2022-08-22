#include <iostream>

class MutationSubject {
  char _mutable_property;

 public:
  MutationSubject(const char mutable_property)
      : _mutable_property{mutable_property} {
    /* establish class invariants */
  }
  void set_mutable_property(const char& mutable_property) {
    _mutable_property = mutable_property;
  }
  char mutable_property() const { return _mutable_property; }
};

void use_the_original(MutationSubject& t) { t.set_mutable_property('f'); }

void use_a_copy(MutationSubject t) { t.set_mutable_property('g'); }

int main() {
  MutationSubject does_mutation_persist('a');
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout << does_mutation_persist.mutable_property();
  use_a_copy(does_mutation_persist);
  std::cout << does_mutation_persist.mutable_property();
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  std::cout << does_mutation_persist.mutable_property();
  use_the_original(does_mutation_persist);
  std::cout << does_mutation_persist.mutable_property();

  return 0;
}
