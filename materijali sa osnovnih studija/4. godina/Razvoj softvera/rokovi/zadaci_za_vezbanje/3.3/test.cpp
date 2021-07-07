#define CATCH_CONFIG_MAIN
#include "catch/single_include/catch2/catch.hpp"
#include "test_class.hpp"

//neki random testovi

TEST_CASE("Song Vector", "[tag]")
{
    SECTION("Initialization", "[]")
    {
        std::vector<std::string> songs = load_songs();

        CHECK(songs.size() == 5);
    }


    SECTION("Swapping", "[]")
    {
        std::vector<std::string> songs = load_songs();
        int a = 1; 
        int b = 3;
        
        std::vector<std::string> swapped_songs = switch_songs(songs, a, b);

        CHECK(songs[a] == swapped_songs[b]);
        CHECK(songs[b] == swapped_songs[a]);
        CHECK_FALSE(songs[a] == swapped_songs[a]);
        CHECK_FALSE(songs[b] == swapped_songs[b]);
    }

}