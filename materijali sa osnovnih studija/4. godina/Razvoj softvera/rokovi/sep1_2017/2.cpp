#include <iostream>
#include <string>
#include <vector>

//tekst nije najjasniji, radio sam ga kao da hoce ispis tipa
//   nesto********
//   nestomaloduze
//   nestomanje***

class Prelom
{
public:
    Prelom(std::vector<std::string> words) 
        : m_words(words) 
    {}

    std::vector<std::string> operator()()
    {
        int max = 0;
        for(const auto &w : m_words)
        {
            if(w.length() > max)
            {
                max = w.length();
            }
        }

        for(auto &w : m_words)
        {
            if(w.length() < max)
            {   
                std::string s( (max-w.length()), '*' );
                w += s;
            }
        }

        return m_words;
    }

private: 
    std::vector<std::string> m_words;
};


int main (){

    std::vector<std::string> words   { "nesto", 
                                       "nestomaloduze",
                                       "nestomanje"
                                     };

    Prelom p(words);

    std::vector<std::string> res = p();
    for(const auto &r : res)
    {
        std::cout << r << std::endl;
    }

    return 0;
}