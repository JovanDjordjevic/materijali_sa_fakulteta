// Zadatak 4
// Koristeći biblioteku range-v3, a bez upotrebe for, while, do-while petlji,
// komande goto, rekurzije, i algortima std::for_each implementirati sledeći
// zadatak:
// Implementirati funkciju count_abbrevs koja broji skracenice u datom vektoru
// reci. Skracenica je rec koja ne sadrzi ni jedno malo slovo.

#include <iostream>
#include <string>
#include <vector>

#include <range/v3/view.hpp>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/numeric/accumulate.hpp>

#include <cassert>

using namespace ranges::v3;
namespace views = ranges::v3::view;
namespace actions = ranges::v3::action;


// POCETAK STUDENTSKOG KODA
bool isAllLower(std::string s){
    auto res = s | view::transform([](char c){if (std::isupper(c)) return 1; else return 0;});
    auto r = std::accumulate(res.begin(), res.end(), 0, [](auto x, auto y){ return  x+y; });
    if(r == 0) return true;
    else return false;
}

// KRAJ STUDENTSKOG KODA

int count_abbrevs(const std::vector<std::string>& words)
{
// POCETAK STUDENTSKOG KODA
    auto result =  words
     | view::filter( [](auto word){ return isAllLower(word); }) | to_vector;
return result.size();
// KRAJ STUDENTSKOG KODA
}

int main(int argc, char **argv)
{
    // Napomena: U niskama su razmaci jedine beline - nema tabulatora
    // i novih redova
    assert((
        count_abbrevs(
            std::vector<std::string>{
                std::string{"MATF"},
                std::string{"banana"},
                std::string{"NPR"},
                std::string{"ini"}
               })
            == 2));

    // std::vector<std::string> words = {
    //             std::string{"MATF"},
    //             std::string{"banana"},
    //             std::string{"ini"}
    //            };

    
    // for(auto r : res)
    //     std::cout << r << std::endl;

    std::cout << "OK" << std::endl;

    return 0;
}