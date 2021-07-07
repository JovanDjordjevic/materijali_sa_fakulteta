#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

//	Dodavanje metoda Lik::Povrsina()

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
	
	const Tacka& Polozaj() const
		{ return Polozaj_; }
		
	double Povrsina() const
		{ return 0; }

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
		
	double Povrsina() const
		{ return Sirina() * Visina(); }
	
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
		
	double Povrsina() const
		{ return R() * R() * M_PI; }
	
private:
	double R_;
};

//--------------------------------------------------
int main()
{
	Pravougaonik p(1,2,3,4);
	cout << p.Polozaj() << " : " << p.Povrsina() 
		 << " : " << p.Sirina() << ',' << p.Visina() << endl;

	Kvadrat kv(1,2,3);
	cout << kv.Polozaj() << " : " << kv.Povrsina() 
		 << " : " << kv.Sirina() << ',' << kv.Visina() << endl;

	Krug k(1,2,3);
	cout << k.Polozaj() << " : " << k.Povrsina() 
		 << " : " << k.R() << endl;

	return 0;
}
