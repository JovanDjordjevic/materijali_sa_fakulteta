#include <iostream>
#include <vector>
#include <functional>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view.hpp>

//zadatak je implmenetirati funkciju filtered_sum koju pozivamo koa u mainu pomocu rangeeve

using namespace ranges::v3;

//ovde smo template stavili jer smo bili lenji, bolje je da navedemo eksplicitno neki tip koji predstavlja
// funkciju koja vraca bool isto i za ostale argumente
template<typename Pred, typename Acc, typename Collection>
Acc filtered_sum(Pred predicate, Acc init, Collection xs)
{   
    //za accumulate nam ne treba prefiks view:: (?)
    return  accumulate (xs | view::filter(predicate), init);
}

int main (int argc, char *argv[])
{   
    std::vector<int> xs {-1, -7, -5, 1, 3, 5};

    std::cout << filtered_sum(
        [](auto val){return val>0;},  //predicate
        0,                            //init  
        xs                            //kolekcija  
    ) << std::endl;

    return 0;
}