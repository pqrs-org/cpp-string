#include <catch2/catch.hpp>

#include <pqrs/string.hpp>

TEST_CASE("trim_left") {
  {
    std::string s("  example  ");
    pqrs::string::trim_left(s);
    REQUIRE(s == "example  ");
  }
}

TEST_CASE("trim_right") {
  {
    std::string s("  example  ");
    pqrs::string::trim_right(s);
    REQUIRE(s == "  example");
  }
}

TEST_CASE("trim") {
  {
    std::string s("  example  ");
    pqrs::string::trim(s);
    REQUIRE(s == "example");
  }
}

TEST_CASE("trim_left_copy") {
  {
    std::string s("  example  ");
    REQUIRE(pqrs::string::trim_left_copy(s) == "example  ");
    REQUIRE(s == "  example  ");
  }
  {
    std::string_view s("  example  ");
    REQUIRE(pqrs::string::trim_left_copy(s) == "example  ");
    REQUIRE(s == "  example  ");
  }
}

TEST_CASE("trim_right_copy") {
  {
    std::string s("  example  ");
    REQUIRE(pqrs::string::trim_right_copy(s) == "  example");
    REQUIRE(s == "  example  ");
  }
  {
    std::string_view s("  example  ");
    REQUIRE(pqrs::string::trim_right_copy(s) == "  example");
    REQUIRE(s == "  example  ");
  }
}

TEST_CASE("trim_copy") {
  {
    std::string s("  example  ");
    REQUIRE(pqrs::string::trim_copy(s) == "example");
    REQUIRE(s == "  example  ");
  }
  {
    std::string_view s("  example  ");
    REQUIRE(pqrs::string::trim_copy(s) == "example");
    REQUIRE(s == "  example  ");
  }
}

TEST_CASE("trim_invalid_right") {
  {
    std::string s("hello\xe6world");
    pqrs::string::trim_invalid_right(s);
    REQUIRE(s == "hello");
  }
}

TEST_CASE("trim_invalid_right_copy") {
  {
    std::string s("hello\xe6world");
    REQUIRE(pqrs::string::trim_invalid_right_copy(s) == "hello");
    REQUIRE(s == "hello\xe6world");
  }
}
