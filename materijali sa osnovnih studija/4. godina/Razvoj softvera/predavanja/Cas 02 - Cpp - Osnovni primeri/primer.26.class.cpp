#include <iostream>
#include <cstring>

using namespace std;

//	Primer implementacije klase "niska".
//	U ovom primeru se sadrzaj smesta u dinamicki alociranom prostoru
//	i zato je neophodno pisanje destruktora i pratecih metoda.

class niska
{
private:
	//	Sakrivamo podatke od spoljnih posmatraca
	char* tekst;
	//	"Prijateljske" funkcije i klase smeju da pristupe implementaciji, 
	//	tj. podatku "tekst". Ako imamo prijateljske funkcije i klase
	//	to obicno ukazuje na gresku u dizajnu, ali u ovom slucaju je
	//	u pitanju prakticno deo definicije klase, pa je u redu.
	friend ostream& operator<<( ostream& ostr, const niska& n );
	
public:	
	niska( const char* s )
	{
		cout << "kosntruktor\n";
		if(s){
			tekst = new char[strlen(s)+1];
			strcpy( tekst, s );
		}else{
			tekst = new char[1];
			*tekst = 0;
		}
	}
	
	niska( const niska& n )
	{	
		cout << "kosntruktor kopije\n";
		tekst = new char[strlen(n.tekst)+1];
		strcpy( tekst, n.tekst );
	}
	
	niska& operator=( const niska& n )
	{	
		cout << "dodela\n";
		//	Provera na pocetku sprecava pogresnu primenu oblika "a = a"
		//	koja bi dovela najpre do brisanja sadrzaja objekta "a"
		//	a zatim i do pokusaja prepisivanja nedefinisanog sadrzaja.
		if( this != &n ){
			//	Uobicajeno, prvi deo je isti kao destruktor...
			delete [] tekst;
			//	...a drugi isti kao konstruktor kopije
			tekst = new char[strlen(n.tekst)+1];
			strcpy( tekst, n.tekst );
			
			//	Alternativni oblik:
			//		niska q(n);
			//		swap(tekst, q.tekst)
			//	  1. napravi se automatski objekat "q" kao kopija "n"
			//	  2. razmeni se sadrzaj ovog objekta i objekta q
			//	  3. automatski se "q" dealocira sa steka
		}
		return *this;
	}
	
	~niska()
	{
		cout << "*** DEL " << (void*)tekst << " " << tekst << endl;
		delete [] tekst;
	}
};

ostream& operator<<( ostream& ostr, const niska& n ) 
{
	ostr << n.tekst;
	return ostr;
}

int main()
{
	niska s = "Zdravo!";
	cout << s << endl;
	niska q = "AAA";
	q = s;
}

