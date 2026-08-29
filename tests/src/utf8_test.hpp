#include <boost/ut.hpp>
#include <pqrs/string.hpp>

#include <array>
#include <string>
#include <string_view>

void run_utf8_test() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "cesu8_to_utf8"_test = [] {
    const std::string fire_cesu8("\xed\xa0\xbd\xed\xb4\xa5", 6);
    const std::string fire_utf8("\xf0\x9f\x94\xa5", 4);
    expect(pqrs::string::cesu8_to_utf8("") == "");
    expect(pqrs::string::cesu8_to_utf8("hello🐱world") == "hello🐱world");
    expect(pqrs::string::cesu8_to_utf8(fire_cesu8) == fire_utf8);
    expect(pqrs::string::cesu8_to_utf8(fire_utf8) == fire_utf8);

    const std::string minimum_surrogate_pair("\xed\xa0\x80\xed\xb0\x80", 6);
    const std::string minimum_four_byte_utf8("\xf0\x90\x80\x80", 4);
    expect(pqrs::string::cesu8_to_utf8(minimum_surrogate_pair) ==
           minimum_four_byte_utf8);

    const std::string maximum_surrogate_pair("\xed\xaf\xbf\xed\xbf\xbf", 6);
    const std::string maximum_utf8("\xf4\x8f\xbf\xbf", 4);
    expect(pqrs::string::cesu8_to_utf8(maximum_surrogate_pair) == maximum_utf8);

    // Valid one-, two-, and three-byte boundaries.
    expect(pqrs::string::cesu8_to_utf8("\x7f") == "\x7f");
    expect(pqrs::string::cesu8_to_utf8("\xc2\x80") == "\xc2\x80");
    expect(pqrs::string::cesu8_to_utf8("\xdf\xbf") == "\xdf\xbf");
    expect(pqrs::string::cesu8_to_utf8("\xe0\xa0\x80") == "\xe0\xa0\x80");
    expect(pqrs::string::cesu8_to_utf8("\xed\x9f\xbf") == "\xed\x9f\xbf");
    expect(pqrs::string::cesu8_to_utf8("\xee\x80\x80") == "\xee\x80\x80");
    expect(pqrs::string::cesu8_to_utf8("\xef\xbf\xbf") == "\xef\xbf\xbf");

    const std::string embedded_null("a\0b", 3);
    expect(pqrs::string::cesu8_to_utf8(embedded_null) == embedded_null);

    // Surrogate state transitions.
    const std::string lead_lead_trail(
        "\xed\xa0\xbd\xed\xa0\x80\xed\xb0\x80",
        9);
    expect(pqrs::string::cesu8_to_utf8(lead_lead_trail) ==
           "�\xf0\x90\x80\x80");
    expect(pqrs::string::cesu8_to_utf8("\xed\xa0\xbdz") == "�z");
    expect(pqrs::string::cesu8_to_utf8("\xed\xb4\xa5\xed\xa0\xbd") ==
           "��");

    // Replace malformed input by maximal subpart, as in replace_invalid_utf8.
    const std::string truncated("\xf0\x9f", 2);
    expect(pqrs::string::cesu8_to_utf8(truncated) == "�");
    expect(pqrs::string::cesu8_to_utf8(truncated) ==
           pqrs::string::replace_invalid_utf8(truncated));

    const std::string unpaired_lead_surrogate("\xed\xa0\xbd", 3);
    expect(pqrs::string::cesu8_to_utf8(unpaired_lead_surrogate) == "�");

    const std::string unpaired_trail_surrogate("\xed\xb4\xa5", 3);
    expect(pqrs::string::cesu8_to_utf8(unpaired_trail_surrogate) == "�");

    expect(pqrs::string::cesu8_to_utf8("\xc0\x80") == "��");
    expect(pqrs::string::cesu8_to_utf8("\xe0\x9f\x80") == "���");
    expect(pqrs::string::cesu8_to_utf8("\xf4\x90\x80\x80") == "����");

    // Do not consume a valid byte following a malformed maximal subpart.
    expect(pqrs::string::cesu8_to_utf8("\xc2z") == "�z");
    expect(pqrs::string::cesu8_to_utf8("\xe1\x80z") == "�z");
    expect(pqrs::string::cesu8_to_utf8("\xf1\x80\x80z") == "�z");
    expect(pqrs::string::cesu8_to_utf8("\x80\xffz") == "��z");

    // Non-surrogate malformed input follows replace_invalid_utf8 semantics.
    constexpr std::array malformed_inputs{
        std::string_view("\xc2", 1),
        std::string_view("\xe1\x80", 2),
        std::string_view("\xf1\x80\x80", 3),
        std::string_view("\xe0\x9f\x80", 3),
        std::string_view("\xf4\x90\x80\x80", 4),
    };
    for (const auto input : malformed_inputs) {
      expect(pqrs::string::cesu8_to_utf8(input) ==
             pqrs::string::replace_invalid_utf8(input));
    }
  };

  "replace_invalid_utf8"_test = [] {
    expect(pqrs::string::replace_invalid_utf8("") == "");
    expect(pqrs::string::replace_invalid_utf8("hello🐱world") == "hello🐱world");
    expect(pqrs::string::replace_invalid_utf8("hello\xe6world") == "hello�world");
    expect(pqrs::string::replace_invalid_utf8("\xc0\xaf") == "��");
    expect(pqrs::string::replace_invalid_utf8("\xe2\x82") == "�");
    expect(pqrs::string::replace_invalid_utf8("\xe2\x82z") == "�z");
  };
}
