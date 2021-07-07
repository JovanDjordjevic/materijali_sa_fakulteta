#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
using namespace std;

// vector

namespace Geometrija {

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
		
		virtual ~Lik() 
			{}
			
		const Tacka& Polozaj() const
			{ return Polozaj_; }
			
		virtual double Povrsina() const = 0;
		virtual const char* NazivKlase() const = 0;
		
		virtual void Ispisi( ostream& ostr ) const {
			ostr << NazivKlase() << Polozaj() << " : P=" << Povrsina();		
		}

	private:
		Tacka Polozaj_;
	};

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
	
} // namespace Geometrija

//--------------------------------------------------
using namespace Geometrija;

int main()
{
	vector<Lik*> niz;
	niz.push_back( new Pravougaonik(1,2,3,4) );
	niz.push_back( new Kvadrat(1,2,3) );
	niz.push_back( new Krug(8,9,10) );
	for( unsigned i=0; i<niz.size(); i++ )
		cout << *niz[i] << endl;
	for( unsigned i=0; i<niz.size(); i++ )
		delete niz[i];
	return 0;
}
