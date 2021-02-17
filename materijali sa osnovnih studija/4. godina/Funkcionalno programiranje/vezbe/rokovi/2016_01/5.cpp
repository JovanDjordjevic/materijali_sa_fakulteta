#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>


int main(int argc, char **argv)
{
    std::string word;
    std::cin >> word;
    int result = std::count_if(word.begin(), word.end(), [](char c){if(std::isupper(c)) return true; else return false;});
    
    if(result == 1){
        std::cout << "IMA tacno jedno veliko slovo" << std::endl;
    }
    else{
        std::cout << "NEMA tacno jedno veliko slovo" << std::endl;
    }
    

    return 0;
}