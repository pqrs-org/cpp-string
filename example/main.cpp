#include <iostream>
#include <pqrs/string.hpp>

int main() {
  std::string example("  example  ");
  pqrs::string::trim_left(example);
  std::cout << "'" << example << "'" << std::endl;

  return 0;
}
