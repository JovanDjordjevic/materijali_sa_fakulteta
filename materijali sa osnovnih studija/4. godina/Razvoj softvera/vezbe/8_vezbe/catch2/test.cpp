//da bismo koristili catch biblioteku moramo prvo da definisisemo ovaj makro pa tek onda da 
//includujemo biblioteku, bitan je redosled
//takodje, za nas ce automatski biti napravljena main funkcija u okviru define-a
//tako da ne moramo sami da pisemo to ispod

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

//int main()... ne mora

#include <vector>
#include <stdexcept> //klassa gde imamo puno predefinisanih exceptiona
#include <iterator>
#include <algorithm>

using namespace std;

//0, 1, 1, 2, 3, 5, 8, 13...
vector<unsigned> fib(int n)
{   
    //primer kako koristimo exception iz zaglavlja, argument je nasa poruka
    if(n < 0) throw invalid_argument("n<0");
    if(n == 0) return {0u};
    if(n == 1) return {0u, 1u};

    auto previous = fib(n-1);
    auto f_n_1 = *(end(previous)-1);
    auto f_n_2 = *(end(previous)-2);
    previous.push_back(f_n_1 + f_n_2);

    return previous;
}

//testove koristimo sa ovim makroom, prvi arg je string ime testa, a drugi arg jes tring tagova u obliku "[tag1][tag2]...."
TEST_CASE("Izracunavanje fibonacijevog niza", "[fib][function]")
{
    //kod za testiranje ide ovde
    //radimo jedinicne testove, i grupisemo ih u SECTIONE
    SECTION("funkcija fib vraca prvih 6 brojeva fib. niza za ulaz 5")
    {
        vector<unsigned> expected = {0, 1, 1, 2, 3, 5};
        //makro koms e prosledi vrednost koju ocekujemo da je tacna
        REQUIRE(fib(5) == expected);
    }
    /*
    //hocemo da vidimo sta se desi kada test padne
    //poretpostavimo da fibonacijev niz ide ovako bez 0:   1, 1, 2...
    SECTION("Funckija fib vraca niz [1,1] za ulaz 1")
    {
        vector<unsigned> expected = {1, 1};
        REQUIRE(fib(1) == expected);
    }
    */

    //jos jedan test
    SECTION("Funckija fib vraca niz koji ima bar jednu jedinicu za ulaz 1")
    {
        const auto result = fib(1);
        const auto number_of_ones = count(begin(result), end(result), 1);
        REQUIRE(number_of_ones >= 1);

        //imamo jos jedan makro koji testira obrnutu stvar or REQUIRE
        //on prolazi ako mu se argument izracunava u false
        REQUIRE_FALSE(number_of_ones<1);
        //generalno je bolje koristiti ovaj makro umesto REQUIRE( !uslov ) 
    }

}