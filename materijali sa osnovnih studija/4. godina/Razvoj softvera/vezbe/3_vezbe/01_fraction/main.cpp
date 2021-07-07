#include <iostream>
#include "Fraction.hpp"

int main(){
    //jedan jedini konstruktor koji smo napisali se moze ponasati kao tri razlicita konstruktora
    //u zavisnosti od toga da li prosledimo 0,1 ili 2 argumenta
    const Fraction r;       // 0/1
    const Fraction r2(5);   // 5/1
    const Fraction r3(2,3); // 2/3
    Fraction r4 = r3.changeDenominator(7);
    Fraction r5 = r2 + r3;

    ++r4;
    r4++;

    std::cout << r5.numerator() << '/' << r5.denominator() << std::endl;
    //objasnjenje za static_cast u implementraciji operatora za cast u double
    std::cout << static_cast<double>(Fraction(1,2)) << std::endl;

    //posto smo implementirali operator za cast u double za razlomak, sada mzoemo uraditi nesto ovako:
    double d = r4; //ali bolje je da nemamo implicitne konverzije i da pisemo double d = static_cast<double>(r4);
    std::cout << d << std::endl;
    
    //implicitna konverzija nam daje da uradimo i nesto ovako (sto uglavnom ne zelimo):
    //const Fraction r6 = 5;
    //std::cout << r6.numerator() << '/' << r6.denominator() << std::endl;  // pisace 5/1
    //ono sto se tu desi je da se implicitno pozove konstruktor sa jednim argumentom, a fix za to je da
    //se u konstruktoru  doda kljucna rec explicit, koja ce onemoguciti ovakvo ponasanje, i ako progamo da pokrenemo sad kod, ovo ce izbaciti gresku

    std::cout << r2;
    return 0;
}