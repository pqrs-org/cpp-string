#include <boost/ut.hpp>
#include <pqrs/string.hpp>

void run_predicate_test() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "starts_with"_test = [] {
    {
      std::string s("1234");
      expect(pqrs::string::starts_with(s, ""));
      expect(pqrs::string::starts_with(s, "1"));
      expect(pqrs::string::starts_with(s, "12"));
      expect(pqrs::string::starts_with(s, "123"));
      expect(pqrs::string::starts_with(s, "1234"));
      expect(!pqrs::string::starts_with(s, "12345"));
      expect(!pqrs::string::starts_with(s, "2"));
      expect(!pqrs::string::starts_with(s, "23456"));
    }
    {
      std::string s("");
      expect(pqrs::string::starts_with(s, ""));
      expect(!pqrs::string::starts_with(s, "1"));
    }
    {
      std::string_view s("1234");
      expect(pqrs::string::starts_with(s, "1"));
    }
  };

  "ends_with"_test = [] {
    {
      std::string s("1234");
      expect(pqrs::string::ends_with(s, ""));
      expect(pqrs::string::ends_with(s, "4"));
      expect(pqrs::string::ends_with(s, "34"));
      expect(pqrs::string::ends_with(s, "234"));
      expect(pqrs::string::ends_with(s, "1234"));
      expect(!pqrs::string::ends_with(s, "01234"));
      expect(!pqrs::string::ends_with(s, "3"));
      expect(!pqrs::string::ends_with(s, "00123"));
    }
    {
      std::string s("");
      expect(pqrs::string::ends_with(s, ""));
      expect(!pqrs::string::ends_with(s, "1"));
    }
    {
      std::string_view s("1234");
      expect(pqrs::string::ends_with(s, "4"));
    }
  };
}
