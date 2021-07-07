#include <vector>
#include <string>
#include <iostream> 
#include <fstream>      

std::vector<std::string> load_songs(){
    std::vector<std::string> songs;
    std::ifstream file("pesme.txt");
    
    while(file.good())
    {   
        std::string song;
        getline(file, song);
        songs.push_back(song);
    }

    file.close();
    return songs;
}

 std::vector<std::string> switch_songs(std::vector<std::string> songs, size_t a, size_t b){
    std::swap(songs[a], songs[b]);
    return songs;    
 }
