//za dat string tipa "aaabbb" uraditi kompresiju tako da se dobije nesto tipa "3a3b" pomocu ranges biblioteke

#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include <range/v3/view.hpp>
#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/to_container.hpp>

#include <range/v3/numeric/accumulate.hpp>

#include <cassert>

using namespace ranges::v3;
namespace views = ranges::v3::view;
namespace actions = ranges::v3::action;


int main(int argc, char **argv)
{

    std::string input;
    std::cin >> input;

    auto result = input 
                | views::group_by(std::equal_to<>())
                | views::transform( [](auto group){
                            auto b = std::begin(group);
                            auto e = std::end(group);
                            auto c = *b;
                            auto num = distance(b, e);
                            return std::to_string(num) + c;
                    } )
                ;

    //ne razumem zasto mi ne radi accumulate ovde iako sam ukljucio zaglavlje, zato se ispisuje kao lista
    //result = accumulate(tmpResult, "");

    std::cout << result << std::endl;

    return 0;
}