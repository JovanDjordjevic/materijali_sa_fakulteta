#include <iostream>
using namespace std;

//	Strukture se prave slicno kao u C-u, ali sada predstavljaju tip.
//	Iza "struct" obavezno stoji ime tipa koji se pravi.
//	Upotreba struktura je kao u C-u.

struct tacka
{
	int x;
	int y;
};

//	Ako hocemo da omogucimo zapisivanje nekog tipa u toku,
//	dovoljno je da napisemo verziju operatora >> za taj tip.
//	Ovaj operator je binarni: prvi argument je referenca na 
//	opsti izlazni tok (ostream&), a drugi const referenca na 
//	objekat koji zelimo da zapisemo. Posto pri pisanju ne menjamo 
//	objekat koji zapisujemo, koristimo const referencu.

//	Uobicajeno je da operatori citanja i pisanja vracaju
//	referencu na ulazni ili izlazni tok, kako bi njihova
//	primena mogla da se nadovezuje:
//		cout << a << b << c 

//	C++ omogucava da predefinisemo postojece operatore.
//	Pri tome ne moze da se menja broj argumenata operatora
//	(osim u slucaju operatora "()", ali o tome kasnije). 
//	Operatori mogu da se definisi u u klasi prvog argumenta,
//	ali i o tome kasnije.

ostream& operator<<( ostream& ostr, const tacka& a ) 
{
	ostr << "(" << a.x << "," << a.y << ")";
	return ostr;
}

//	Slicno i za citanje, ali pri citanju menjamo objekat koji citamo
//	pa zato nije const. Takodje, moramo da vodimo racuna o ispravnosti
//	zapisa, a ako primetimo gresku onda i da promenimo stanje toka.

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
	tacka a = {2,5};
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
