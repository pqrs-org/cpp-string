#include <boost/ut.hpp>
#include <pqrs/string.hpp>

void run_trim_test() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "trim_left"_test = [] {
    {
      std::string s("  example  ");
      pqrs::string::trim_left(s);
      expect(s == "example  ");
    }
    {
      std::string s("\t\n  example  ");
      pqrs::string::trim_left(s);
      expect(s == "example  ");
    }
  };

  "trim_right"_test = [] {
    {
      std::string s("  example  ");
      pqrs::string::trim_right(s);
      expect(s == "  example");
    }
    {
      std::string s("  example  \t\n");
      pqrs::string::trim_right(s);
      expect(s == "  example");
    }
  };

  "trim"_test = [] {
    {
      std::string s("  example  ");
      pqrs::string::trim(s);
      expect(s == "example");
    }
    {
      std::string s(" \t\n ");
      pqrs::string::trim(s);
      expect(s == "");
    }
  };

  "trim_left_copy"_test = [] {
    {
      std::string s("  example  ");
      expect(pqrs::string::trim_left_copy(s) == "example  ");
      expect(s == "  example  ");
    }
    {
      std::string_view s("  example  ");
      expect(pqrs::string::trim_left_copy(s) == "example  ");
      expect(s == "  example  ");
    }
  };

  "trim_right_copy"_test = [] {
    {
      std::string s("  example  ");
      expect(pqrs::string::trim_right_copy(s) == "  example");
      expect(s == "  example  ");
    }
    {
      std::string_view s("  example  ");
      expect(pqrs::string::trim_right_copy(s) == "  example");
      expect(s == "  example  ");
    }
  };

  "trim_copy"_test = [] {
    {
      std::string s("  example  ");
      expect(pqrs::string::trim_copy(s) == "example");
      expect(s == "  example  ");
    }
    {
      std::string_view s("  example  ");
      expect(pqrs::string::trim_copy(s) == "example");
      expect(s == "  example  ");
    }
  };

  "trim_invalid_right"_test = [] {
    {
      std::string s("hello\xe6world");
      pqrs::string::trim_invalid_right(s);
      expect(s == "hello");
    }
    {
      std::string s("hello");
      pqrs::string::trim_invalid_right(s);
      expect(s == "hello");
    }
  };

  "trim_invalid_right_copy"_test = [] {
    {
      std::string s("hello\xe6world");
      expect(pqrs::string::trim_invalid_right_copy(s) == "hello");
      expect(s == "hello\xe6world");
    }
  };
}
