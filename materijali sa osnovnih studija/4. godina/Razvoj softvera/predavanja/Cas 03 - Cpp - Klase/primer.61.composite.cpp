#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

// kompozitna klasa (nekompletna)

namespace Geometrija {

	//--------------------------------------------------
	class Tacka
	{
	public:
		Tacka( double x, double y )
			: X_(x), Y_(y)
			{}
			
		~Tacka() {  
			cout << "~Tacka " << *this << endl; 
		}

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
			{ BrojLikova++; }
			
		Lik( const Lik& lik )
			: Polozaj_( lik.Polozaj_ )
			{ BrojLikova++; }

		virtual ~Lik() { 
			cout << "~Lik" << endl;
			BrojLikova--; 
		}
		
		const Tacka& Polozaj() const
			{ return Polozaj_; }

		virtual double Povrsina() const = 0;
		virtual const char* NazivKlase() const = 0;

		virtual void Ispisi( ostream& ostr ) const {
			ostr << NazivKlase() << Polozaj() << " : P=" << Povrsina();		
		}
		
		static unsigned BrojLikova;

	private:
		Tacka Polozaj_;
	};

	unsigned Lik::BrojLikova = 0;

	ostream& operator<<( ostream& ostr, const Lik& lik )
	{
		lik.Ispisi(ostr);
		return ostr;
	}

	//--------------------------------------------------
	class Pravougaonik : public Lik
	{
	public:
		Pravougaonik( double x, double y, double s, double v )
			: Lik(x,y), Sirina_(s), Visina_(v)
			{}

		~Pravougaonik() { 
			cout << "~Pravougaonik" << endl;
		}

		double Sirina() const
			{ return Sirina_; }

		double Visina() const
			{ return Visina_; }

		const char* NazivKlase() const
			{ return "Pravougaonik"; }
		
		double Povrsina() const
			{ return Sirina() * Visina(); }

		void Ispisi( ostream& ostr ) const {
			Lik::Ispisi(ostr);
			ostr << " : a,b=" << Sirina() << "," << Visina();
		}

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

		~Kvadrat() { 
			cout << "~Kvadrat" << endl;
		}

		const char* NazivKlase() const
			{ return "Kvadrat"; }
	};

	//--------------------------------------------------
	class Krug : public Lik
	{
	public:
		Krug( double x, double y, double r )
			: Lik(x,y), R_(r)
			{}
		
		~Krug() {
			cout << "~Krug" << endl; 
		}
		
		double R() const
			{ return R_; }

		const char* NazivKlase() const
			{ return "Krug"; }
		double Povrsina() const
			{ return R() * R() * M_PI; }

		void Ispisi( ostream& ostr ) const {
			Lik::Ispisi(ostr);
			ostr << " : r=" << R();
		}	
	private:
		double R_;
	};
	
	//--------------------------------------------------
	class SlozenLik : public Lik 
	{
	public:
		SlozenLik( double x, double y )
			: Lik(x,y)
			{}
		
		~SlozenLik() {
			cout << "~SlozenLik" << endl;
			for( auto lik: Likovi_ )
				delete lik;
		}
			
		void Dodaj( Lik* l )
			{ Likovi_.push_back(l); }
		
		double Povrsina() const {
			double p = 0;
			for( auto lik: Likovi_ )
				p += lik->Povrsina();
			return p;			
		}

		const char* NazivKlase() const
			{ return "SlozenLik"; }
		
	private:
		vector<Lik*> Likovi_;
	};

} // namespace Geometrija

//--------------------------------------------------
using namespace Geometrija;

int main()
{
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
	cout << Lik::BrojLikova << endl;
	}
	//svi likovi su obrisani

	cout << Lik::BrojLikova << endl;

	return 0;
}

