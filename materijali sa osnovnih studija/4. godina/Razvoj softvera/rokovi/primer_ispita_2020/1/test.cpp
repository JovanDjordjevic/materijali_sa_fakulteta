#define CATCH_CONFIG_MAIN
#include "catch/single_include/catch2/catch.hpp"

#include "encoder.hpp"

// POCETAK_STUDENTSKOG_KODA
// Mozete pisati sve testove u jednom slucaju ili ih razdvajati u vise slucajeva

TEST_CASE("Encoder", "[class]") 
{   
    SECTION("When Encoder is constructed with a number, the number is not zero", "[constructor]")
    {
        int n = 5;

        Encoder e(n);
        int pi = e.getPi();

        REQUIRE(n == pi);
    }

    SECTION("Testing call operator for lowercase string only, no overflow", "[call][nooverflow]")
    {   
        int n = 1;
        std::string testString = "beans";
        std::string expected = "cfbot";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }

    SECTION("Testing call operator for lowercase string only, with overflow", "[call][overflow]")
    {   
        int n = 55;
        std::string testString = "beanz";
        std::string expected = "ehdqc";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }

    SECTION("Testing call operator for lowercase string only, with negative number", "[call][negative]")
    {   
        int n = -27;
        std::string testString = "beanz";
        std::string expected = "adzmy";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }

    SECTION("Testing call operator for uppercase string only", "[call][uppercase]")
    {   
        int n = 1235;
        std::string testString = "AAWFAF";
        std::string expected = "NNJSNS";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }

    SECTION("Testing call operator for number string only", "[call][number]")
    {   
        int n = -5;
        std::string testString = "1234567890";
        std::string expected = "6789012345";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }

    SECTION("Testing call operator for special string only", "[call][special]")
    {   
        int n = -1124;
        std::string testString = "(*&(&%))";
        std::string expected = "########";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }

    SECTION("Testing call operator for mixesd string", "[call][mixed]")
    {   
        int n = 53;
        std::string testString = "iuha&*)(*JA@GGa2@#%%!55AGAWG";
        std::string expected = "jvib#####KB#HHb3#####66BHBXH";
        

        Encoder e(n);
        std::string result = e(testString);

        REQUIRE(result == expected);
    }
}

// KRAJ_STUDENTSKOG_KODA
