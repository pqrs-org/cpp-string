#include "trim_test.hpp"
#include "truncate_test.hpp"
#include "utf8_test.hpp"

int main() {
  run_trim_test();
  run_truncate_test();
  run_utf8_test();

  return 0;
}
