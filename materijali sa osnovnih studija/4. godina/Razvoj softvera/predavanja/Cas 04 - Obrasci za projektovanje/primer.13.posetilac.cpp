#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

//	Zbog deklarisanja klase PosetilacLikova i njenih metoda 'unapred'
//	moramo da unapred deklariseno i klase hijerarhije.

class Pravougaonik;
class Kvadrat;
class Krug;
class SlozenLik;

class PosetilacLikova
{
public:
	virtual void PosetiPravougaonik( Pravougaonik& ) = 0;
	virtual void PosetiKvadrat( Kvadrat& ) = 0;
	virtual void PosetiKrug( Krug& ) = 0;
	virtual void PosetiSlozenLik( SlozenLik& ) = 0;
};


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
	
	// Klasican pristup problemu racunanja povrsine.
	virtual double Povrsina() const = 0;

	//	Opsti metod za prihvatanje posete.
	virtual void PrihvatiPosetu( PosetilacLikova& p ) = 0;

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
		
	//	Pravougaonik prihvata 'opstu' posetu tako sto usmerava posetioca 
	//	da poseti bas pravougaonik.
	void PrihvatiPosetu( PosetilacLikova& p )
	{
		p.PosetiPravougaonik( *this );
	}
	
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

	//	Kvadrat prihvata 'opstu' posetu tako sto usmerava posetioca 
	//	da poseti bas kvadrat.
	void PrihvatiPosetu( PosetilacLikova& p )
	{
		p.PosetiKvadrat( *this );
	}
	
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
	
	//	Krug prihvata 'opstu' posetu tako sto usmerava posetioca 
	//	da poseti bas krug.
	void PrihvatiPosetu( PosetilacLikova& p )
	{
		p.PosetiKrug( *this );
	}

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
		
	//	Slozen lik prihvata 'opstu' posetu tako sto usmerava posetioca da poseti slozen lik,
	//	ali i svaki pojedinacan sadrzani lik.
	void PrihvatiPosetu( PosetilacLikova& p )
	{
		p.PosetiSlozenLik( *this );
		for( auto lik: Likovi_)
			lik->PrihvatiPosetu(p);		
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

class RacunanjePovrsine : public PosetilacLikova
{
public:
	RacunanjePovrsine()
		: Povrsina_(0)
		{}

	RacunanjePovrsine( Lik& lik )
		: Povrsina_(0)
	{
		lik.PrihvatiPosetu(*this);
	}

	double Povrsina() const 
		{ return Povrsina_; }

	//mozemo predefinisait ponasanje operatora kastovanja neke vrednosti u double
	operator double()
		{ return Povrsina(); }

	void PosetiPravougaonik( Pravougaonik& p ){
		Povrsina_ += p.Sirina() * p.Visina();
	}
		
	void PosetiKvadrat( Kvadrat& k ){
		Povrsina_ += k.Sirina() * k.Visina();
	}
	
	void PosetiKrug( Krug& k ){
		Povrsina_ += k.R() * k.R() * M_PI;
	}
	
	void PosetiSlozenLik( SlozenLik& ){
	}

private:
	double Povrsina_;
};

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
	
	cout << RacunanjePovrsine(sl) << endl;

	return 0;
}

