#include <iostream>
using namespace std;

//	Izdvajamo zajednicke elemente klasa Pravougaonik
//	i Krug u klasu Lik. Menjamo Pravougaonik i Krug
//	tako da nasledjuju Lik.

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
class Lik
{
public:
	Lik( double x, double y )
		: Polozaj_(x,y)
		{}
	
	//const iza funkcije kaze da ova funkcija nece menjati stanje objekta. prvi const je deo const Tack&, tj vracenu referencu
	//na tacku necemo moci da menjamo, tj necmeo moci da menjamo tacku na koju & pokazuje
	const Tacka& Polozaj() const
		{ return Polozaj_; }

private:
	Tacka Polozaj_;
};

//--------------------------------------------------
class Pravougaonik : public Lik
{
public:
	Pravougaonik( double x, double y, double s, double v )
		: Lik(x,y), Sirina_(s), Visina_(v)
		{}
		
	double Sirina() const
		{ return Sirina_; }
	
	double Visina() const
		{ return Visina_; }
	
private:
	double Sirina_;
	double Visina_;
};

//--------------------------------------------------
class Kvadrat : public Pravougaonik
{
public:
	Kvadrat( double x, double y, double a )
		: Pravougaonik( x, y, a, a )
	{}
};

//--------------------------------------------------
class Krug : public Lik
{
public:
	Krug( double x, double y, double r )
		: Lik(x,y), R_(r)
		{}

	double R() const
		{ return R_; }
	
private:
	double R_;
};

//--------------------------------------------------
int main()
{
	Tacka t(20,15);
	cout << t << endl;
	
	Pravougaonik p(1,2,3,4);
	cout << p.Polozaj() << " : " << p.Sirina() << ',' << p.Visina() << endl;

	Kvadrat kv(1,2,3);
	cout << kv.Polozaj() << " : " << kv.Sirina() << ',' << kv.Visina() << endl;

	Krug k(1,2,3);
	cout << k.Polozaj() << " : " << k.R() << endl;

	return 0;
}
