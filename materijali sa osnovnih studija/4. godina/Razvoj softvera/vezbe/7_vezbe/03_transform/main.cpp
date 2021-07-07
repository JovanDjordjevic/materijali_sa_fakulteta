// Zadatak: Dat je vektor pojmova (niski).
// Konstruisati novi vektor koji odgovara datom,
// tako da ukoliko je pojam odabran (pocinje karakterom '*'),
// onda vektor na toj poziciji ima vrednost true,
// a u suprotnom ima vrednost false.
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

int main(int argc, char *argv[])
{
    std::vector<std::string> items{
        "aardvark",
        "compunctious",
        "**congratulations**",
        "contrafribblarity",
        "contrary",
        "dictionary",
        "**interphrastical**",
        "**patronise**",
        "**pericombobulation**",
        "phrasmotic",
        "**syllables**"};

        using namespace std;

        vector<bool> selection_markers(items.size());

        //transform uzima [) interval jedne kolekcije i smesta rezultat funkcije koja je cetvrti argument
        //u durugu kolekciju pocev od prosledjenog iteratora
        //koa cetvrti arg moze i lambda funkc
        transform(cbegin(items), cend(items), begin(selection_markers), is_selected);

        //ispis na cout
        copy(cbegin(selection_markers), cend(selection_markers), ostream_iterator<bool>(cout, "\n"));

    return 0;
}