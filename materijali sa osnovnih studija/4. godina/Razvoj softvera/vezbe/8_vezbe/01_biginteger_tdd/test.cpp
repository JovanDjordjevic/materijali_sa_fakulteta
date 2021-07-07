//NOTE: nije dovrsio ovaj zadatak, vidi njegove materijale

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "BigInteger.hpp"

TEST_CASE("create the BigInteger","[BigInteger]")
{
    SECTION("Ween BigInteger is default-constructed, its value is zero")
    {
        const BigInteger bigInt;
        const auto expected{0};
        
        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructedfrom one digit, its value is number in that string")
    {   
        auto numStr{"1"};
        const BigInteger bigInt{numStr};
        const auto expected{1};

        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed from more than one digits, number of digits is euqal to string size")
    {   
        const string numStr{"1234"};
        const BigInteger bigInt{numStr};
        const auto expected{numStr.size()};

        const auto result{bigInt.numberOfDigits()};

        REQUIRE(result == expected);
    }

    SECTION("When BigInteger is constructed from more than one digits, its value is the number in the string")
    {   
        const string numStr{"1234"};
        const BigInteger bigInt{numStr};
        const auto expected{1234};

        const auto result{bigInt.toInt()};

        REQUIRE(result == expected);
    }
}