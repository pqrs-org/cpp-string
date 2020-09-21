#include <catch2/catch.hpp>

#include <pqrs/string.hpp>

TEST_CASE("starts_with") {
  {
    std::string s("1234");
    REQUIRE(pqrs::string::starts_with(s, ""));
    REQUIRE(pqrs::string::starts_with(s, "1"));
    REQUIRE(pqrs::string::starts_with(s, "12"));
    REQUIRE(pqrs::string::starts_with(s, "123"));
    REQUIRE(pqrs::string::starts_with(s, "1234"));
    REQUIRE(!pqrs::string::starts_with(s, "12345"));
    REQUIRE(!pqrs::string::starts_with(s, "2"));
    REQUIRE(!pqrs::string::starts_with(s, "23456"));
  }
  {
    std::string s("");
    REQUIRE(pqrs::string::starts_with(s, ""));
    REQUIRE(!pqrs::string::starts_with(s, "1"));
  }
  {
    std::string_view s("1234");
    REQUIRE(pqrs::string::starts_with(s, "1"));
  }
}

TEST_CASE("ends_with") {
  {
    std::string s("1234");
    REQUIRE(pqrs::string::ends_with(s, ""));
    REQUIRE(pqrs::string::ends_with(s, "4"));
    REQUIRE(pqrs::string::ends_with(s, "34"));
    REQUIRE(pqrs::string::ends_with(s, "234"));
    REQUIRE(pqrs::string::ends_with(s, "1234"));
    REQUIRE(!pqrs::string::ends_with(s, "01234"));
    REQUIRE(!pqrs::string::ends_with(s, "3"));
    REQUIRE(!pqrs::string::ends_with(s, "00123"));
  }
  {
    std::string s("");
    REQUIRE(pqrs::string::ends_with(s, ""));
    REQUIRE(!pqrs::string::ends_with(s, "1"));
  }
  {
    std::string_view s("1234");
    REQUIRE(pqrs::string::ends_with(s, "4"));
  }
}
