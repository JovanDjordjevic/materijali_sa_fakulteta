#include <iostream>
using namespace std;


//	Strukture u C++-u mogu da imaju i "metode".
//	Terminologija C++-a je specificna:
//		- atributi su "clanovi podaci"
//		- metodi su "clanovi funkcije" ili "funkcije clanice"

//	Omogucene su deklaracije vidljivosti: 
//		- public:		- imena vide svi
//		- protected:	- imena vide samo struktura i njeni naslednici
//		- private:		- imena vidi samo ova struktura

//	Kljucna rec 'struct' je slicna kao kljucna rec 'class' osim sto:
//		- podrazumevana vidljivost za 'struct' je 'public',
//		  a za 'class' je 'private'
//		- klucna rec 'struct' ne moze da se koristi na nekim mestima
//		  za oznacavanje tipskih promenljivih, a 'class' moze 
//		  (kasnije vise o tome)

//	Kljucan metod svake strukture i klase je "konstruktor".
//	Konstruktor opisuje inicijalizaciju objekata.
//	Svaki objekat se inicijalizuje konstruktorom. 
//	Ako ga ne napisemo mi, prevodilac obezbedjuje podrazumevani
//	konstruktor bez argumenata, koji inicijalizuje sve podatke
//	odgovarajucim podrazumevanim konstruktorima.

//	Konstruktor je metod koji se zove kao i klasa i ne vraca rezultat.
//	Izvrsava se odmah nakon alokacije prostora za objekat:
//		- najpre se inicijalizuju nasledjeni delovi
//		- zatim se inicijalizuju clanovi podaci
//		- na kraju se izvrsava telo konstruktora
//	Deo iza ':' je "lista inicijalizacija" i opisuje
//	kako i kojim konstruktorima se inicijalizuju elementi objekta.
//	Redosled inicijalizacija ne zavisi od redosleda u listi
//	vec samo od redosleda podataka u definiciji klase.
//	Ako se ne navede lista inicijalizacija, ili se neki elementi
//	ne navede u njoj, inicijalizacija se obavlja odgovarajucim 
//	konstruktorima bez argumenata. 

struct tacka
{
public:
	int x;
	int y;
	
	tacka( int x0, int y0 )
		: x(x0), y(y0)
	{}
};

ostream& operator<<( ostream& ostr, const tacka& a ) 
{
	ostr << "(" << a.x << "," << a.y << ")";
	return ostr;
}

istream& operator>>( istream& istr, tacka& a )
{
	char c1,c2,c3;
	istr >> c1 >> a.x >> c2 >> a.y >> c3;
	if( c1!='(' || c2!=',' || c3!=')' )
		istr.setstate( ios::failbit );
	return istr;
}

int main()
{
	tacka a(2,5);
	cout << a << endl;
	cout << "Upisite tacku: ";
	cin >> a;
	if( !cin ){
		cerr << "Greska!" << endl;
		return 1;
	}
	cout << a << endl;

	return 0;
}