#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "encoder.hpp"

#include <string>

using namespace std;

// POCETAK_STUDENTSKOG_KODA
// Mozete pisati sve testove u jednom slucaju ili ih razdvajati u vise slucajeva

TEST_CASE("Encoder", "[class]") 
{    
    SECTION("Encoder is constructible from a single integer", "[constructor]")
    {
        // Arrange
        auto step = 0;

        // Act-Assert
        REQUIRE_NOTHROW(Encoder{step});
    }

    SECTION("When supplied with an empty string, Encoder with a random step returns an empty string", "[operator()]")
    {
        // Arrange
        auto random_step = 10;
        Encoder enc{random_step};
        const auto input = string{};
        const auto expected = string{};

        // Act
        const auto result = enc(input);

        // Assert
        REQUIRE(expected == result);
    }

    SECTION("Given a string with one invalid character, Encoder with a random step returns a string with one hash", "[operator()]")
    {
        // Arrange
        auto random_step = -20;
        Encoder enc{random_step};
        const auto input = string{" "};
        const auto expected = string{"#"};

        // Act
        const auto result = enc(input);

        // Assert
        REQUIRE(expected == result);
    }

    SECTION("Given a string with one valid lowercase letter in a single cycle, Encoder returns a string with one valid encoded character", "[operator()]")
    {
        // Arrange
        auto step = 3;
        Encoder enc{step};
        const auto input = string{"a"};
        const auto expected = string{"d"};

        // Act
        const auto result = enc(input);

        // Assert
        REQUIRE(expected == result);
    }

    SECTION("Given a string with one valid lowercase letter outside of a single cycle, Encoder returns a string with one valid encoded character", "[operator()]")
    {
        // Arrange
        auto step = -255;
        Encoder enc{step};
        const auto input = string{"f"};
        const auto expected = string{"k"};

        // Act
        const auto result = enc(input);

        // Assert
        REQUIRE(expected == result);
    }

    SECTION("Given a string with two or more characters, Encoder returns a string with valid encoded characters", "[operator()]")
    {
        // Arrange
        auto step = 1;
        Encoder enc{step};
        const auto input = string{"abc-DEF.678'xyz"};
        const auto expected = string{"bcd#########yza"};

        // Act
        const auto result = enc(input);

        // Assert
        REQUIRE(expected == result);
    }
}

// KRAJ_STUDENTSKOG_KODA
