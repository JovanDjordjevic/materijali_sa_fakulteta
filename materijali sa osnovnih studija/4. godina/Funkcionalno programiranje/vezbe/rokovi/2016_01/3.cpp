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

bool isName( std::string s){
    if (std::isupper(*std::begin(s))) 
    {   
        auto res = s | views::transform( [](auto x){ if(std::isupper(x)) return 1; else return 0; } )
                     | view::filter( [](auto x){ if(x==1) return true; else return false; } )
                     | to_vector;
        if(res.size() == 1)
            return true;
        else return false;
    }
    else return false;
}


//Beans memeS MEMES aaaaa YaYaYA aPPa

int main(int argc, char **argv)
{
    
    auto words = istream_range<std::string>(std::cin) | to_vector;
    auto result = words | views::filter(&isName) | views::take(5);
    std::cout << result << std::endl;

    return 0;
}