#include <string>
#include <iostream>
#include <fstream>
#include <numeric>

class LyricShuffler
{
    public:
        LyricShuffler(std::string filepath);
        std::string toString();
        void operator()(int a, int b);

        std::vector<std::pair<int, std::string>> lyrics;
};


LyricShuffler::LyricShuffler(std::string filepath)
{
    std::ifstream file(filepath);
    std::string line;
    int lyricCounter = 1;

    while(file.good())
    {
        getline(file, line);
        if( line != "" )
        {
            lyrics.emplace_back(lyricCounter, line);
            lyricCounter++;
        }
    }

    file.close();
}

std::string LyricShuffler::toString()
{   
    std::string acc = "";
    std::string result = std::accumulate( std::begin(lyrics) , std::end(lyrics), acc,
                                        [](std::string acc, std::pair<int, std::string> elem)
                                        {
                                            acc += std::to_string(elem.first);
                                            acc += " ";
                                            acc += elem.second;
                                            acc += "\n";

                                            return acc;
                                        });
    return result;
}

void LyricShuffler::operator()(int a, int b)
{
    std::swap(lyrics[a], lyrics[b]);
}