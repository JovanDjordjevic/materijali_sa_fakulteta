#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

//ovo je isto kao primer sa proslog casa, samo je ovde da bi se ukazalo da 
//na njena nadogradjujemo kod za observer pattern (?)

//----------------------------------------------------------------
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

//----------------------------------------------------------------
class Lik
{
public:
	Lik( double x, double y )
		: Polozaj_(x,y)
		{}
	
	virtual ~Lik()
		{}
	
	virtual Lik* Kopija() const = 0;

	const Tacka& Polozaj() const
		{ return Polozaj_; }

	Tacka& Polozaj()
		{ return Polozaj_; }
	
	virtual double Povrsina() const = 0;
	
private:
	Tacka Polozaj_;
};

ostream& operator<<( ostream& ostr, const Lik& l )
{
	ostr << l.Polozaj() << " P=" << l.Povrsina();
	return ostr;
}

//----------------------------------------------------------------
class Pravougaonik : public Lik
{
public:
	Pravougaonik( double x, double y, double s, double v )
		: Lik(x,y), Sirina_(s), Visina_(v)
		{}
	
	Lik* Kopija() const
		{ return new Pravougaonik(*this); }

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

//----------------------------------------------------------------
class Kvadrat : public Pravougaonik
{
public:
	Kvadrat( double x, double y, double a )
		: Pravougaonik( x, y, a, a )
		{}

	Lik* Kopija() const
		{ return new Kvadrat(*this); }
};

//----------------------------------------------------------------
class Krug : public Lik
{
public:
	Krug( double x, double y, double r )
		: Lik(x,y), R_(r)
		{}
	
	Lik* Kopija() const
		{ return new Krug(*this); }

	double R() const
		{ return R_; }
	
	double Povrsina() const
		{ return R() * R() * M_PI; }
	
private:
	double R_;
};

//----------------------------------------------------------------
class SlozenLik : public Lik 
{
public:
	SlozenLik( double x, double y )
		: Lik(x,y)
		{}
	
	SlozenLik( const SlozenLik& sl )
		: Lik(sl)
		{ init( sl ); }
	
	~SlozenLik()
		{ deinit(); }
	
	SlozenLik& operator=( const SlozenLik& sl )
	{
		if( &sl != this ){
			deinit();
			Polozaj() = sl.Polozaj();
			init(sl);
		}
		return *this;
	}
		
	Lik* Kopija() const
		{ return new SlozenLik(*this); }

	void Dodaj( Lik* l )
		{ Likovi_.push_back(l); }
	
	double Povrsina() const
	{
		double p = 0;
		for( auto lik: Likovi_ )
			p += lik->Povrsina();
		return p;			
	}

private:
	vector<Lik*> Likovi_;
	
	void deinit()
	{
		for( auto lik: Likovi_ )
			delete lik;
		Likovi_.clear();
	}
	
	void init( const SlozenLik& sl )
	{
		for( auto lik: sl.Likovi_ )
			Dodaj( lik->Kopija() );
	}
};

//----------------------------------------------------------------

int main()
{
	SlozenLik sl(0,0);
	sl.Dodaj( new Pravougaonik(1,2,3,4) );
	sl.Dodaj( new Kvadrat(5,6,7) );
	sl.Dodaj( new Krug(8,9,10) );
	SlozenLik* sl2 = new SlozenLik(1,1);
	sl2->Dodaj( new Krug(2,3,4));
	sl2->Dodaj( new Kvadrat(2,4,5));
	sl.Dodaj(sl2);
	cout << sl << endl;

	return 0;
}

