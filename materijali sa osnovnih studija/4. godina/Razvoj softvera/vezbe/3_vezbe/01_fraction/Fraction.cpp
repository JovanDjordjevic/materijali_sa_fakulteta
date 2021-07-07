#include "Fraction.hpp"   //nasi headeri koriste "" a ne <>

// kada zaelimo da implementiramo metod neke klase  van deklaracije klase (nama je to u hpp-u)
// potrebno je da oznacimo da je ono sto implementiramo bas metod te klase, sa :: (to dodje kao neki namespace)
// primetimo da u definiciji funkcije nemamo navodjenje default vrednosti, ali praksa je da se ponekad to u
// definiciji stavi kao komentar da nebi stalno skakali izmedju cpp i hpp fajla da proverimo
Fraction::Fraction(int numerator /*=0*/, unsigned denominator /*=1*/)
    : m_numerator(numerator), m_denominator(denominator)
{
    // umesto klasicne inicijalizacije u kostruktoru, cesce se koriste liste inicijalizacija
    // : ime_polja_klase(cime_se_inicijalizuje), ...
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
    //dobra peaksa je nikako ne uzimati direktno polja klase nego koristiti getere
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
{   //prefiksni ++ 
    auto newNumerator = numerator() + denominator();
    numerator(newNumerator);
    return *this;  //u c++ this je pokazivac na nas objekat (pa moramo da ga dereferenciramo), u ovom slucaju Fraction*
}

Fraction Fraction::operator++(int)
{   //postfiksni ++
    //za postfiksni moramo prvo zapamtiti startu vrednost, onda uvecati, i onda vratiti STARU vrednost
    Fraction tmp(numerator(), denominator());
    //auto newNumerator = numerator() + denominator();
    //numerator(newNumerator);
    //psoto u sustini ovde uvecavanje radimo isto kao za prefiksni, mzoemo samo da pozovemo tu funkciju da nebi ponavljali kod
    ++(*this);
    return tmp;
}

Fraction::operator double() const
{
    //return numerator() / (double)denominator();
    //u c++ se trudimo da c-ovsko kastovanje kao iznad ne koristimo
    //kada unapred znamo koji se tip kastuje u koji, 
    //koristimo kljucnu rec static_cast<tip_u_sta_kastujemo>( izraz_koji_kastujemo )
    return numerator() / static_cast<double>( denominator() );
    //imamo i reinterpret_cast<>(), pogledati u dokumentaciju
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

//operatore >> i << implementiramo kao funkcije a ne kao metode klase tako da nam ne treba Fraction::
std::istream &operator>>(std::istream &in, Fraction &f)
{
    int numerator;
    char c;
    unsigned denominator;
    in >> numerator >> c >> denominator;  //unos ocekujmeo u obliku x/y pa nam terba char da pokupi /
    //f.numerator(numerator);
    //f.denominator(denominator);
    //ako bismo pisali samo ove dve linije gore, dobili bismo gresku. To je zato sto se trenutno nalazimo u funkciji definisanoj van klase
    //samim tim mi odavde ne mozemo da vidimo privatne metode nominator() i denominator(). Ovo mozemo prevazici koriscenjem
    //konceptra prijatelja klasa. Prijatelj neke klase mozez biti: funkcija, metod neke durge klase, cela druga klasa
    //prijatelji mogu da vide privatne metode klase. Nakon sto oznacimo da su funkcije friend, sad mzoemo napisati onako:
    f.numerator(numerator);
    f.denominator(denominator);

    return in;
}

std::ostream &operator<<(std::ostream &out, const Fraction &f)
{
    //upisemo u dobijeni tok sta treba
    out << f.numerator() << '/' << f.denominator();
    //i vratimo ga. Ima smisla da u deklaraciji bude & bas da ovde nebi bilo kopiranja
    return out;
}
