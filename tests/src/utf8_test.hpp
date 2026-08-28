#include <boost/ut.hpp>
#include <pqrs/string.hpp>

void run_utf8_test() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "replace_invalid_utf8"_test = [] {
    expect(pqrs::string::replace_invalid_utf8("") == "");
    expect(pqrs::string::replace_invalid_utf8("hello🐱world") == "hello🐱world");
    expect(pqrs::string::replace_invalid_utf8("hello\xe6world") == "hello�world");
    expect(pqrs::string::replace_invalid_utf8("\xc0\xaf") == "��");
    expect(pqrs::string::replace_invalid_utf8("\xe2\x82") == "�");
    expect(pqrs::string::replace_invalid_utf8("\xe2\x82z") == "�z");
  };
}
