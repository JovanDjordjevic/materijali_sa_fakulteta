#include <iostream>
#include <vector>
#include <functional>
#include <range/v3/view.hpp>

//range je biblioteka koja nam omogucava pipelining operacija
//hocemo da napisemo nekakav haskell-like code
//hocemo da krenemo od neke kolekcije, i da primenjujemo funkcije viseg reda i da to nekako pipeline-ujemo
//i zelimo da se lenjo radi, tj da nista ne radimo dok se bas ne zahteva 
//npr accumulate $ filter $ transform $ [kolekcija]

//range je header only biblioteka, dovoljno je samo da se skine sa neta i da se includuje
//priemtimo da smo stavili namesapce samo range::v3, a ne range::v3::view. Razlog je zbog citljivosti, u view imamo razne funksije
//koje se zovu isto kao one iz standarne biblioteke, pa je lepse da znamo tacno odakle je koja
using namespace ranges::v3;
using namespace std::placeholders; //zaprimere gde smo korsitili bind

int main (int argc, char *argv[])
{   
    std::vector<int> xs {-1, -7, -5, 1, 3, 5};

    //hocemo npr da uradimo apsolutni vrednost svih elemenata manjih od 6 i da od toga napravimo niz stringova
    //konstruktija range-a  je implicitna, samo stavimo | 

    //primetimo da je slozenost ovoga O(1), a ne O(n), zato sto view radi lenjo
    //mi akda napisemo ovaj kod, nista zapravo nismo izracunali nego smo napravili neki pametni iterator koji ce proci 
    //kroz kolekciju tek kada za tim bude bilo potrebe

    auto results = 
        xs | view::transform(abs)
           | view::filter([](const int &x){ return x < 6; })
            //ovaj filter mogli smo i bez labda funkcije, vec da koristimo funkcionalne objekte
            //koristimo bind, njime radimo slicnu stvar kaos to imamo u haskelu, da od funkcije vise arguemnata napravimo funkciju manje argumenata
            //npr, ovde smo od funkcije less koja ima 2  arg, napravili funkciju <6 koja ima 1 arg, _1 je palcehoder, a 6 je konkretna vrednost
            //    | view::filter(std::bind(std::less<>(), _1, 6))
           |view::transform([](auto value){ return std::to_string(value); } )
           ;

    //tek ovde ce biti izracunato
    for (auto value : results){
        std::cout << value << std::endl;
    }

    return 0;
}