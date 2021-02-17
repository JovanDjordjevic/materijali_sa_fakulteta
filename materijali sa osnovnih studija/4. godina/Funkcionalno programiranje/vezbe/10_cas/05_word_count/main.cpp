#include <iostream>
#include <vector>
#include <functional>

#include <range/v3/view.hpp>
#include <range/v3/action.hpp>
#include <range/v3/view/istream.hpp>         //ovde je istream_range

using namespace ranges::v3;

//brojimo pojavljivanja najfrekventnijih reci iz file.txt
//na vezbama je ovo testirao sledecom komandom:
//  cat -ns file.txt | ./a.out
//nije zapravo otvarao fajl pa parvio stream od fajla

std::string string_to_lower(const std::string &s)
{   
    //ovo to<std::string>() konvertuje rezultat koji dobijemo iz transform u std::string
    return s | view::transform(tolower) | to<std::string>();
}

std::string string_only_alnum(const std::string &s)
{   
    //ovo to<>(std::string) konvertuje rezultat koji dobijemo iz filter u std::string
    return s | view::filter(isalnum) | to<std::string>();
}

int main (int argc, char *argv[])
{       
    //pod efaultu ako nemamo arg, nekispise 10 najfrekventnijih
    const int n = argc <= 1 ? 10 : atoi(argv[1]);

    const auto words = 
        //istream_range<> nam daje da proslednjeni argument koji je istream, 
        //automatski konvertujemo u range objekata tipa koji damo u <>
        istream_range<std::string>(std::cin)
        | view::transform(string_only_alnum)
        | view::transform(string_to_lower)
        | view::remove_if(&std::string::empty) //uklonicemo i prazne stringove iz trenutne kolekcije. Ovde je moglo i sa filter
        | to_vector         //funkcija iz range, konvertuje nasu trenutku kolekciju  u random access kolekciju
                            //taj tip kolekcije nam treba da bi uradili sortiranje sa action::sort
        | action::sort
        ;

        //za sada imamo ovako nesto:
        // ["abc", "abc", "the", "the", "you" ...]

        const auto results = 
            words | view::group_by(std::equal_to<>())   //ovde je mogla i lambda umesto funkcionalnog obejkta
                                                        //group_by ce sve iste reci da nam ubaci u zasebnu listu
                  | view::transform([](const auto &group){
                      const auto begin = std::begin(group);
                      const auto end = std::end(group); 
                      const int size = distance(begin, end);   //ovo je distance iz range biblioteke
                      const std::string word = *begin;
                      return std::make_pair(size, word);
                  })
                  | to_vector
                  | action::sort
                  ;

        //psoto funkcije iz action mutiraju klolekciju (?), umesto da obrcemo listu pa da iteriramo,
        //mozemo  samo da iteriramo unazad
        for (auto value : results | view::reverse | view::take(n))
            std::cout << value.first << ": " << value.second << std::endl;

    return 0;
}
