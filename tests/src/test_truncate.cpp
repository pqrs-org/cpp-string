#include <catch2/catch.hpp>

#include <pqrs/string.hpp>

TEST_CASE("truncate") {
  REQUIRE(pqrs::string::truncate("1234567890", 20, "...") == "1234567890");
  REQUIRE(pqrs::string::truncate("1234567890", 10, "...") == "1234567890");
  REQUIRE(pqrs::string::truncate("1234567890", 9, "...") == "123456...");
  REQUIRE(pqrs::string::truncate("1234567890", 9, "....") == "12345....");
  REQUIRE(pqrs::string::truncate("1234567890", 9, "........") == "1........");
  REQUIRE(pqrs::string::truncate("1234567890", 9, ".........") == "123456789");
  REQUIRE(pqrs::string::truncate("1234567890", 9, "..........") == "123456789");
  REQUIRE(pqrs::string::truncate("1234567890", 4) == "1...");
  REQUIRE(pqrs::string::truncate("1234567890", 3) == "123");
  REQUIRE(pqrs::string::truncate("1234567890", 2) == "12");
  REQUIRE(pqrs::string::truncate("1234567890", 1) == "1");
  REQUIRE(pqrs::string::truncate("1234567890", 0) == "");

  // string_view
  REQUIRE(pqrs::string::truncate(std::string_view("1234567890"), 5) == "12...");
}
