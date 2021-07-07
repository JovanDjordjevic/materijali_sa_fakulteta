// Zadatak: Napisati sablonsku funkciju slide_selection koja prihvata
// iteratore na pocetak i kraj dela kolekcije i iterator na poziciju
// ispred koje se pomeraju elementi datog dela kolekcije.
// Funkcija treba da izvrsi dato pomeranje i vrati par iteratora
// koji pokazuju na pomereni deo kolekcije.

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <utility> //za pair 

template<typename It>
std::pair<It, It> slide_selection(It selection_begin, It selection_end, It destination)
{
    auto it = std::rotate(selection_begin, selection_end, destination);
    return {it, destination};
}

int main()
{   
    using namespace std;

    std::vector<std::string> items{
        "aardvark",
        "compunctious",
        "**congratulations**", // +2 --> selection_begin
        "**contrafribblarity**",
        "**contrary**",
        "dictionary", // +5 --> selection_end
        "interphrastical",
        "patronise", // +7 --> destination
        "pericombobulation",
        "phrasmotic",
        "syllables"};

    // - - * * * + + - - - -   
    //  rotate() =>
    // - - + + * * * - - - -  
    //ovo ce da nam uradi std::rotate(), prima tri argumenta, prvi je iterator na prvi element intervala 
    //na kom se vrsi rotacija (prva * u prvom redu), drugi je iterator na element koji ce postati prvi nakon sto se rotacija izvrsi
    //(prvi + u prvom redu) i iterator na kraj intervala za rotaciju (tj iterator koji pokazuje izmedju + i - u prvom redu)
    //rotate moze kao povratnu vrednost imati iterator na stari prvi element nakon pomeranja (prva * u drugom redu)

    //pisao je funkciju jer treba da vrati par(?)
    auto [nb, ne] = slide_selection(begin(items)+2, begin(items)+5, begin(items)+7);
    //ispis
    //copy(nb, ne, ostream_iterator<string>(cout, "\n"));
    copy(begin(items), end(items), ostream_iterator<string>(cout, "\n"));

    //NOTE: na casu je uradio samo ovaj pri slucaj, kada je destination nakon intervala,
    //u materijalima ima i ostale slucajeve

    return 0;
}