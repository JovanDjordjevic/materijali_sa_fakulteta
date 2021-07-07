#include <iostream>
#include <string>
#include "pair.h"

int main()
{
    using namespace std;
    //primetimo da ako ostavimo samo (3, "tri") auto ce da dedukuje da je to pair<int, const char*>
    //tj uzima se bas taj tip vrednosti koju napisemo, ako hocemo bas std::string, moramo da kastujemo
    auto p = matf::make_pair(3, std::string{"tri"});
    //mozemo i eksplicitnod a navedemo koji tipovi ce biti (pri cemu ce se automatki raditi potrebno kastovanje ako je moguce):
    auto p1 = matf::make_pair<int, std::string>(3, "tri");

    cout << p1.first_ << ", " << p1.second_ <<endl;

    //ako su u klasi polja javna mozemo da radimo strukturnu dekompoziciju kao u pajtonu
    //BITNO: dekompozicija vraca elemente onim redom kojim su  navedeni u klasi
    const auto [first, second] = p1;
    //mozemo i kombinovati sve ovo u jednu liniju:
    //const auto [first, second] = matf::make_pair<int, std::string>(3, "tri");
    cout << first << ", " << second <<endl;
    

    return 0;
}