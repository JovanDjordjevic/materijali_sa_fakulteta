#include <iostream>
using namespace std;

//	Kao i u C-u, objekti mogu da se alociraju automatski i dinamicki.
//	Automatski alocirani objekti se prave pri deklarisanju=definisanju 
//	i unistavaju pri izlasku iz opsega vazenja.
//	Dinamicki alocirani objekti se prave i unistavaju eksplicitno.

//	Zivotni vek svakog objekta u C++-u:
//		- alokacija
//		- inicijalizacija (konstruktor)
//		- upotreba
//		- deinicijalizacija (destruktor)
//		- dealokacija

//	Automatski objekti:
//		- definicija je 'aktivna naredba' a ne samo deklaracija
//			- alokacija na steku
//			- inicijalizacija (konstruktor)
//		- pri izlasku iz opsega vazenja automatski
//			- deinicijalizacija (destruktor)
//			- dealokacija

//	Dinamicki objekti:
//		- pozivanjem operatora "new"
//			- dinamicka alokacija na hipu 
//			  (ili drugacije ako je operator predefinisan, vise kasnije)
//			- inicijalizacija (konstruktor)
//		- pozivanjem operatora "delete"
//			- deinicijalizacija (destruktor)
//			- dealokacija na hipu 
//			  (ili drugacije ako je operator predefinisan)

//	VAZNO!!! Niposto ne kombinovati upotrebu new/delete sa malloc/free.
//	Radi se o razlicitim zonama memorije i mehanizmima (de)alokacije
//	i pratecim postupcima.

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

void automatskiPrimer()
{
	//	Tacka "t" se pravi na pocetku funkcije i unistava pre povratka.
	tacka t(35,4);
	cout << t << endl;
	for( int i=0; i<3; i++ ){
		//	Tacka "t1" se pravi na pocetku svakog ciklusa i unistava 
		//	na njegovom kraju.
		tacka t1(i,i+1);
		cout << t1 << endl;
	}
}

void dinamickiPrimer()
{
	//	Tacka "t" se pravi pozivanjem operatora "new".
	tacka* t = new tacka(35,4);
	cout << *t << endl;
	//	Tacka "t" se unistava pozivanjem operatora "delete".
	delete t;
	for( int i=0; i<3; i++ ){
		//	Tacka "t1" se pravi dinamicki pozivanjem operatora "new".
		//	Inicijalizuje se odgovarajucim konstruktorom.
		tacka* t1 = new tacka(i,i+1);
		cout << *t1 << endl;
		//	Tacka "t1" se unistava pozivanjem operatora "delete".
		delete t1;
	}
}

int main()
{
	automatskiPrimer();
	dinamickiPrimer();
	return 0;
}
