#include "catch.hpp"
#include "encoder.hpp"

TEST_CASE("Test constructor", "encoder")
{

    SECTION("It should return provided number of steps after it's constructed")
    {
        encoder e{5};
        REQUIRE(e.getStep() == 5);
    }
}

TEST_CASE("Test encoding", "encoder")
{

    SECTION("It should return empty string if empty string is provided")
    {
        encoder e{5};
        string encoded = e("");
        REQUIRE(encoded == "");
    }
    SECTION("It should return # when invalid single char string is provided")
    {
        encoder e{5};
        string encoded = e(".");
        REQUIRE(encoded == "#");
    }
    SECTION("It should return encoded string when single upper letter is provided")
    {
        encoder e{1};
        string encoded = e("A");
        REQUIRE(encoded == "B");
    }
    SECTION("It should return encoded string when single lower letter is provided")
    {
        encoder e{-55};
        string encoded = e("a");
        REQUIRE(encoded == "d");
    }
    SECTION("It should return encoded string when single number is provided")
    {
        encoder e{-2};
        string encoded = e("0");
        REQUIRE(encoded == "8");
    }
}