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

  // UTF-8
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 1) == "");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 2) == "");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 3) == "");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 4) == "...");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 5) == "...");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 6) == "...");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 7) == "🐱...");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 15) == "🐱🐱🐱...");
  REQUIRE(pqrs::string::truncate("🐱🐱🐱🐱🐱", 30) == "🐱🐱🐱🐱🐱");

  // Invalid UTF-8
  REQUIRE(pqrs::string::truncate("hello\xe6world", 5) == "he...");
  REQUIRE(pqrs::string::truncate("hello\xe6world", 10) == "hello...");
  REQUIRE(pqrs::string::truncate("hello\xe6world", 12) == "hello�w...");
}
