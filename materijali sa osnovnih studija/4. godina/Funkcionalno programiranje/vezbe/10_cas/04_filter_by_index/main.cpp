#include <iostream>
#include <vector>
#include <functional>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view.hpp>

using namespace ranges::v3;

//zadatak je da filtriramo po neparnom idneksu, kao onos to smo radili u haskellu pre nekoliko vezbi

bool index_filter(size_t index)
{
    return index % 2 != 0;
}

int main (int argc, char *argv[])
{   
    std::vector<int> xs {-1, -3, -5, 1, 2, 3};

    auto results = 
        // xs | zip(...)    zip ovde ne moze ovako da se pajpuje nego mora da se xs da kao argument:
        //zipujemo sa beskonacnom listom, ints pravi listu, od 1, do drugog argumenta,  unreachable je kao palceholder za beskonacno
          view::zip(xs, view::ints(1, unreachable))   
        | view::filter([](auto value){ return index_filter(value.second);})
        | view::transform([](auto value){return value.first;})
        ;

    return 0;
}