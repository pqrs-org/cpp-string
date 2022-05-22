#include <boost/ut.hpp>
#include <pqrs/string.hpp>

void run_truncate_test() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "truncate"_test = [] {
    expect(pqrs::string::truncate("1234567890", 20, "...") == "1234567890");
    expect(pqrs::string::truncate("1234567890", 10, "...") == "1234567890");
    expect(pqrs::string::truncate("1234567890", 9, "...") == "123456...");
    expect(pqrs::string::truncate("1234567890", 9, "....") == "12345....");
    expect(pqrs::string::truncate("1234567890", 9, "........") == "1........");
    expect(pqrs::string::truncate("1234567890", 9, ".........") == "123456789");
    expect(pqrs::string::truncate("1234567890", 9, "..........") == "123456789");
    expect(pqrs::string::truncate("1234567890", 4) == "1...");
    expect(pqrs::string::truncate("1234567890", 3) == "123");
    expect(pqrs::string::truncate("1234567890", 2) == "12");
    expect(pqrs::string::truncate("1234567890", 1) == "1");
    expect(pqrs::string::truncate("1234567890", 0) == "");

    // string_view
    expect(pqrs::string::truncate(std::string_view("1234567890"), 5) == "12...");

    // UTF-8
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 1) == "");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 2) == "");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 3) == "");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 4) == "...");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 5) == "...");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 6) == "...");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 7) == "🐱...");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 15) == "🐱🐱🐱...");
    expect(pqrs::string::truncate("🐱🐱🐱🐱🐱", 30) == "🐱🐱🐱🐱🐱");

    // Invalid UTF-8
    expect(pqrs::string::truncate("hello\xe6world", 5) == "he...");
    expect(pqrs::string::truncate("hello\xe6world", 10) == "hello...");
    expect(pqrs::string::truncate("hello\xe6world", 12) == "hello�w...");
  };
}
