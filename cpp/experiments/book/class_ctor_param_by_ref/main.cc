#include <iostream>

class SaveReference {
 public:
  SaveReference(const double& subject_of_experiment)
      : _subject_of_experiment{subject_of_experiment} {}
  double _subject_of_experiment;
};

int main() {
  // stores an arbitary value of no significance
  double does_my_mutation_affect_object_property = 5;
  SaveReference s{does_my_mutation_affect_object_property};

  std::cout << "Should be 5: " << s._subject_of_experiment << '\n';

  does_my_mutation_affect_object_property = 10;
  std::cout << "Is it still 5? " << s._subject_of_experiment << '\n';
}
