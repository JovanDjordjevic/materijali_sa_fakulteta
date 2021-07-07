#include <iostream>
using namespace std;

//	Inicijalizacija i deinicijalizacija su tesno vezani.
//	Deinicijalizacija je neophodna ako se u objektu koriste 
//	neki spoljni resursi:
//		- dinamicki alocirani objekti
//		- mrezni resursi
//		- drugi resursi OS-a
//		- i sl.
//	Ako je neophodna deinicijalizacija, onda moraju da se pisu bar 
//	sledeca tri vazna metoda:
//		- destruktor (koji vrsi deinicijalizaciju)
//		- operator dodeljivanja 
//			(deinic. staru vrednost pre prepisivanja i inic. nove)
//		- konstruktor kopije (ili "konstruktor kopiranjem")
//			(prepisuje novu vrednost i razdvaja je od originalne kopije)

//	U slucaju klase "tacka" sve to nije neophodno, 
//	zato sto podrazumevane verzije sasvim dobro rade posao, 
//	ali pisemo u narednom primeru radi ilustracije.

class tacka
{
public:
	int x;
	int y;
	
	//	Mozemo da imamo vise konstruktora, 
	//	sve dok im se razlikuju broj i tipovi argumenata.
	
	//	Konstruktor bez argumenata.
	//	Cesto se pogresno naziva 'podrazumevani konstruktor', ali to nije 
	//	ispravno - "podrazumevani konstruktor" je konstruktor bez 
	//	argumenata koji ce obezbediti prevodilac ako autor klase 
	//	ne napise nijedan konstruktor.
	tacka()
		: x(0), y(0)
	{}
	
	tacka( int x0, int y0 )
		: x(x0), y(y0)
	{}
	
	//	"Konstruktor kopije" prepisuje vrednost datog objekta 
	//	u novi objekat i po potrebi alocira nove resurse.
	tacka( const tacka& t )
		: x(t.x), y(t.y)
	{}
	
	//	"Destruktor" je metod bez argumenata koji ima ime klase 
	//	sa prefiksom "~". Svaka klasa ima *tacno jedan* destruktor. 
	//	Ako ga ne napisemo, pravi se podrazumevani destruktor koji 
	//	deinicijalizuje sve podatke primenom autom. deinicijalizacije.
	~tacka()
	{}

	//	"Operator dodeljivanja" prepisuje vrednost datog objekta u nas 
	//	objekat. Po potrebi deinicijalizuje prethodnu i inicijalizuje 
	//	novu vrednost. Po semantici, trebalo bi da radi isto sto i 
	//	kombinacija destruktor + konstruktor kopije.
	//	Uobicajeno je da vraca objekat kome je dodeljena vrednost, 
	//	kako bi dodeljivanja mogla da se nadovezuju.
	tacka& operator=( const tacka& t )
	{ 
		x = t.x;
		y = t.y;
		return *this;
	}	
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
	tacka t1(1,2);
	tacka t2(3,4);
	tacka niz_automatski[2];
	tacka t3(t1);

	for( int i=0; i<3; i++ ){
		tacka t4 = t2;
	}
	t3 = t2;

	//	Operator "new[]" alocira niz objekata i svaki element niza
	//	inicijalizuje konstruktorom bez argumenata.
	tacka* niz_dinamicki = new tacka[3];
	//	Operator delete[] poziva destruktor svakog pojedinacnog elementa 
	//	niza i zatim dealokaciju citavog prostora koji je niz zauzimao.
	delete [] niz_dinamicki;

	//	Oprezno! Ako se alokacija vrsi sa "new[]" onda i dealokacija mora 
	//	sa "delete[] a ne sa "delete", pri cemu prevodilac obicno to 
	//	ne ume da primeti. 
	//	Naredni primer je namerno pogresan, da bi se videlo da se pri 
	//	upotrebi "delete" destruktor ne poziva za svaki od elemenata niza
	// 	(!!! u nekim slucajevima program cak i puca, 
	//	na primer MINGW/G++ prevodilac)
	niz_dinamicki = new tacka[2];
	delete niz_dinamicki;
	
	return 0;
}
