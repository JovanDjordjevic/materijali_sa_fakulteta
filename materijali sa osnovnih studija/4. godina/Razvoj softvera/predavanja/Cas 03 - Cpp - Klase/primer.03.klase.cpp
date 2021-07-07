#include <iostream>
using namespace std;

//	Dodajemo novu klasu Pravougaonik.
//	Pravougaonik ima stranice paralelne koordinatnim osama.
//	Odredjen je polozajem jednog temena i duzinama stranica.

//--------------------------------------------------
class Tacka
{
public:
	Tacka( double x, double y )
		: X_(x), Y_(y)
		{}
		
private:
	double X_;
	double Y_;
	
	friend ostream& operator<<( ostream&, const Tacka& );
	friend istream& operator>>( istream&, Tacka& );
};

//--------------------------------------------------
ostream& operator<<( ostream& ostr, const Tacka& t )
{
	ostr << "(" << t.X_ << "," << t.Y_ << ")";
	return ostr;
}

istream& operator>>( istream& istr, Tacka& a )
{
	char c1,c2,c3;
	istr >> c1 >> a.X_ >> c2 >> a.Y_ >> c3;
	if( c1!='(' || c2!=',' || c3!=')' )
		istr.setstate( ios::failbit );
	return istr;
}

//--------------------------------------------------
class Pravougaonik
{
public:
	Pravougaonik( double x, double y, double s, double v )
		: Polozaj_(x,y), Sirina_(s), Visina_(v)
		{}
		
	const Tacka& Polozaj() const
		{ return Polozaj_; }
	
	double Sirina() const
		{ return Sirina_; }
	
	double Visina() const
		{ return Visina_; }
	
private:
	Tacka Polozaj_;
	double Sirina_;
	double Visina_;
};

//--------------------------------------------------
int main()
{
	Tacka t(20,15);
	cout << t << endl;
	
	Pravougaonik p(1,2,3,4);
	cout << p.Polozaj() << " : " << p.Sirina() << ',' << p.Visina() << endl;

	return 0;
}
