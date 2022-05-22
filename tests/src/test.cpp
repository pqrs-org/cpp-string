#include "predicate_test.hpp"
#include "trim_test.hpp"
#include "truncate_test.hpp"

int main(void) {
  run_predicate_test();
  run_trim_test();
  run_truncate_test();

  return 0;
}
