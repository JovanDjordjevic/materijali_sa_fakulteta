#include "Fraction.hpp"

Fraction::Fraction(int numerator /*=0*/, unsigned denominator /*=1*/)
    : m_numerator(numerator), m_denominator(denominator)
{
    reduce_fraction();
}

int Fraction::numerator() const
{
    return m_numerator;
}

unsigned Fraction::denominator() const
{
    return m_denominator;
}

Fraction Fraction::changeDenominator(unsigned value) const
{   
    Fraction r(numerator(), value);
    return r;    
}

Fraction Fraction::operator+(const Fraction& other) const
{
    Fraction result(
        other.denominator() * numerator() + denominator() * other.numerator(),
        denominator() * other.denominator()
    );
    return result;
}

Fraction Fraction::operator++()
{
    auto newNumerator = numerator() + denominator();
    numerator(newNumerator);
    return *this;
}

Fraction Fraction::operator++(int)
{
    Fraction tmp(numerator(), denominator());
    ++(*this);
    return tmp;
}

//NOVO:
Fraction::operator QString() const
{
    //Qtring ima metod number(arg) konvertuje iz broja u QString
    return QString::number(numerator()) + "/" + QString::number(denominator());
}

Fraction::operator double() const
{
    return numerator() / static_cast<double>( denominator() );

}

void Fraction::numerator(int value)
{
    m_numerator = value;
    reduce_fraction();
}

void Fraction::denominator(unsigned value)
{
    m_denominator = value;
    reduce_fraction();
}

void Fraction::reduce_fraction()
{
    //za domaci, naci nzd i podeliti oba sa nzd
}

std::istream &operator>>(std::istream &in, Fraction &f)
{
    int numerator;
    char c;
    unsigned denominator;
    in >> numerator >> c >> denominator;
    f.numerator(numerator);
    f.denominator(denominator);

    return in;
}

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    out << f.numerator() << '/' << f.denominator();
    return out;
}
