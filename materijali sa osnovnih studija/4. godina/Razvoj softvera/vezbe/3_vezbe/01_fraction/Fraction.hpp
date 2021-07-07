#ifndef FRACTION_HPP
#define FRACTION_HPP

#include<iostream>

//zadatak je bio napraviti Fraction klasu na osnovu nekog datog UML dijagrama

//obicno je praksa da se u hpp fajlu deklarise klasa, a da se u cpp fajlu implementiraju njene metode

class Fraction{
public:
    //ako zelimo da parametri funkcije imaju neku default vrednost ako se ne proslede u pozivu funkcije, to navodimo
    //ISKLJUCIVO U DEKLARACIJI!! sa = ta_vrednost. I takodje, ako neki parametar ima podrazumevanu vrednost,
    //onda svi nakon njega MORAJU imati default vrednosti!
    //kljucna rec explicit nam onemogucava implicitne pozive konstruktora, vidi primer u main.cpp
    explicit Fraction(int numerator = 0, unsigned denominator = 1);
    int numerator() const;         //ako nakon deklaracije dodamo cosnt, garantujemo da ovaj metod nece menjati stanje objekta
    unsigned denominator() const;

    Fraction changeDenominator(unsigned value) const;
    //u c++ mzoemo rpedefinisati neke operatore, i to mzoemo kao metod klase ili kao funkciju
    //razlika je samo sto ce kao metod primiti 1 arg, a kao funkcija 2 arg
    //takodje argumenti i sam tip funkcije moraju biti const
    //primeti da se funkcija predefinisanja operatora uvek zove operator+, operator-, operator<< ...
    Fraction operator+(const Fraction& other) const;
    //prefikstni ++
    Fraction operator++();
    //psotifiksni ++. Posto se oba operatora zovu isto, i oba bi imala potpis funkcije operator() bez argumenata,
    //dogovoreno je da sepostfiksni oepratori koji imaju iprefiskni oblik dopune sa 'int' kao argumentom
    //taj int se nikada zapravo ne koristi vec je tu samo da bismo mogli da razlikujemo funkcije
    Fraction operator++(int);
    //operator konverzije u double, on se obelezava ovako(sa razmakom), nemamo povratnu vrednost jer je podrazumevana
    // povratna vrednost double, to je zbog toga da potpis nebi bio 'double operator double () const; 
    operator double() const;


private:    //mozemo sve u jedan private, ali lepse je da metode i polja budu u razlicitim 
    //primetimo da ode imamo metode koje se zovu isto kao i gore, c++ nam dozvoljava overload
    //primetimo da se razlikuju ne samo po argumentima nego i po konstantnosti
    void numerator(int value);
    void denominator(unsigned value);
    void reduce_fraction();
    //prijateljske funkcije, vidi implementaciju operatora >> u Fraction.cpp zasto smo ovo uradili
    //iako van klase imamo deklaraciju ovih funkcija, potrebno je u klasi oznaciti da su friend
    friend std::istream &operator>>(std::istream &in, Fraction &f);
    friend std::ostream &operator<<(std::ostream &out, const Fraction &f);

private:
    int m_numerator;
    unsigned m_denominator;
};

//operatore >> i << definisemo kao funckije
//>> mora kao prvi arg da primi apstraktnu klasu istream (to je klasa za sve ulazne tokove) (po referenci)
//drugi arg je ono u sta cemo upisati vrednost iz toka (isto po referenci, da nebi bilo kopiranja (?))
//citanje sa toka MENJA taj tok tako da ne moze biti konstantan, isto i za obj u koji upisujemo
//povratna vrednost mora biti opet istream da bismo mogli da nadovezujemo  >> a >> b i on opet mora biti po referenci
std::istream &operator>>(std::istream &in, Fraction &f);
//slicno za <<, samo sto je ostream klasa za izlazne tokove, ali sada posto se objekat koji se ispisuje ne menja, on moze biti konstantan
std::ostream &operator<<(std::ostream &out, const Fraction &f);

#endif  //za FRACTION_HPP