// Zadatak: Napisati sablonsku funkciju is_sorted koja za datu kolekciju
// proverava da li je sortirana neopadajuce.

#include <iostream>
#include <string>
#include <numeric>
#include <vector>

//slicnu ideju imamo kao u proslom zadatku
//Hooloovo | o
//ooloovoo
//u skalarnom cemo kao mnozenje koristiti operaciju poredjenja <=
//recicemo npr da ce ovo vratiti bool vrednost, (mogli smo i sa int kao u proslom)
//dobicemo nesto TTFTTTFT i onda kao sabiranje mozemo da radimo konjukciju tih vrednmosti T && T && T... i ako je bar neki F dobicemo false na kraju

template<typename C, typename Inner = typename C::value_type>
bool is_sorted(const C& xs)
{
    using namespace std;
    //neutral je true zato sto koristimo &&
    //ne zaboravi redosled, prvo definisemo +
    //a onda na kraju *
    return inner_product(begin(xs), end(xs)-1, begin(xs)+1, true,
            [](const bool left, const bool right){return left && right;},
            [](const Inner &left, const Inner &right){return left <= right;} );
}

int main(int argc, char *argv[])
{
    const std::string text = "Hooloovoo";
    std::cerr << text << ": " << is_sorted(text) << std::endl;

    const std::string word = "Almost";
    std::cerr << word << ": " << is_sorted(word) << std::endl;

    const std::vector<int> numbers{1, 2, 3, 3, 4, 5, 6, 6, 7};
    std::cerr << "numbers: " << is_sorted(word) << std::endl;

    return 0;
}
