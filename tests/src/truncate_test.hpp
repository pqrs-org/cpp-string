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

    // UTF-8 boundary values
    expect(pqrs::string::truncate("\xc2\x80", 100) == "\xc2\x80");
    expect(pqrs::string::truncate("\xe0\xa0\x80", 100) == "\xe0\xa0\x80");
    expect(pqrs::string::truncate("\xed\x9f\xbf", 100) == "\xed\x9f\xbf");
    expect(pqrs::string::truncate("\xf0\x90\x80\x80", 100) == "\xf0\x90\x80\x80");
    expect(pqrs::string::truncate("\xf4\x8f\xbf\xbf", 100) == "\xf4\x8f\xbf\xbf");

    // Overlong sequences, surrogate code points, and values over U+10FFFF
    expect(pqrs::string::truncate("\xc0\xaf", 100) == "��");
    expect(pqrs::string::truncate("\xe0\x9f\x80", 100) == "���");
    expect(pqrs::string::truncate("\xed\xa0\x80", 100) == "���");
    expect(pqrs::string::truncate("\xf0\x8f\x80\x80", 100) == "����");
    expect(pqrs::string::truncate("\xf4\x90\x80\x80", 100) == "����");
    expect(pqrs::string::truncate("\xf5\x80\x80\x80", 100) == "����");

    // Stray continuation bytes and interrupted or truncated sequences
    expect(pqrs::string::truncate("\x80\x80", 100) == "��");
    expect(pqrs::string::truncate("\xe2\x82", 100) == "�");
    expect(pqrs::string::truncate("\xe2\x82z", 100) == "�z");
    expect(pqrs::string::truncate("\xf0\x91\x92", 100) == "�");
    expect(pqrs::string::truncate("\xf1\xbfz", 100) == "�z");

    // Unicode Standard 3.9.6, Tables 3-8 through 3-11
    expect(pqrs::string::truncate("\xc0\xaf\xe0\x80\xbf\xf0\x81\x82\x41", 100) ==
           "��������A");
    expect(pqrs::string::truncate("\xed\xa0\x80\xed\xbf\xbf\xed\xaf\x41", 100) ==
           "��������A");
    expect(pqrs::string::truncate("\xf4\x91\x92\x93\xff\x41\x80\xbf\x42", 100) ==
           "�����A��B");
    expect(pqrs::string::truncate("\xe1\x80\xe2\xf0\x91\x92\xf1\xbf\x41", 100) ==
           "����A");
  };
}
