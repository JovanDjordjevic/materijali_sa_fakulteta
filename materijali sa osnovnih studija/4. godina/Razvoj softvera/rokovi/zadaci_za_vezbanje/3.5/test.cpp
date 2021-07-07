#define CATCH_CONFIG_MAIN
#include "catch/single_include/catch2/catch.hpp"
#include "test_class.hpp"

TEST_CASE("Initialization", "[init]")
{
    SECTION("When constructed, lyrics are loaded", "[constructor]")
    {
        std::string filepath = "datoteka.txt";

        LyricShuffler ls(filepath);

        CHECK_FALSE(ls.lyrics.empty());
    }

    SECTION("When constructed, lyrics vector is the correct size", "[constructor]")
    {
        std::string filepath = "datoteka.txt";

        LyricShuffler ls(filepath);

        CHECK(ls.lyrics.size() == 9);
    }

    SECTION("toString() test", "[constructor]")
    {
        std::string filepath = "datoteka.txt";
        std::string end = "\n";
        std::string expected_result = "1 Honno sabishisa ga" + end + 
                                      "2 Konna watashi o" + end + 
                                      "3 Tsuyoku shitekureru" + end + 
                                      "4 Myakuutsu kodou" + end + 
                                      "5 Shizukana hodo" + end + 
                                      "6 Kikoeru hazu deshou" + end + 
                                      "7 Ima wa mada hitomi tojite" + end + 
                                      "8 Mimi o sumasu no" + end + 
                                      "9 Kokoro no SIGNAL" + end;

        LyricShuffler ls(filepath);
        std::string result = ls.toString();

        CHECK(result == expected_result);
    }

    SECTION("swap test", "[call]")
    {
        std::string filepath = "datoteka.txt";
        LyricShuffler ls(filepath);
        std::vector<std::pair<int, std::string>> beforeSwap(ls.lyrics);

        ls(1, 4);
        std::vector<std::pair<int, std::string>> afterSwap = ls.lyrics;

        CHECK(beforeSwap[1] == afterSwap[4]);
        CHECK(beforeSwap[4] == afterSwap[1]);
        CHECK_FALSE(beforeSwap[1] == afterSwap[1]);
        CHECK_FALSE(beforeSwap[4] == afterSwap[4]);
    }
}