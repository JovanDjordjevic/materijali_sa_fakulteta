//uzeli smo Fraction klasu sa proslih vezbi da nebi implementirali opet sve
//u ovde i u cpp dodajemo nove neke stvari

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include<iostream>

//implementiracemo metod koji ce neki ulaz da konvertuje u QString
//Qt ima svoje implementacije za neke tipove i uvek cemos e truditi da koristimo te Q tipove
#include <QString>

class Fraction{
public:
    explicit Fraction(int numerator = 0, unsigned denominator = 1);
    int numerator() const;
    unsigned denominator() const;

    Fraction changeDenominator(unsigned value) const;
    Fraction operator+(const Fraction& other) const;
    Fraction operator++();
    Fraction operator++(int);
    operator double() const;
    operator QString() const;    //NOVO: operator kastovanja u QString

private:
    void numerator(int value);
    void denominator(unsigned value);
    void reduce_fraction();
    friend std::istream &operator>>(std::istream &in, Fraction &f);
    friend std::ostream &operator<<(std::ostream &out, const Fraction &f);

private:
    int m_numerator;
    unsigned m_denominator;
};

std::istream &operator>>(std::istream &in, Fraction &f);
std::ostream &operator<<(std::ostream &out, const Fraction &f);

#endif  //za FRACTION_HPP
