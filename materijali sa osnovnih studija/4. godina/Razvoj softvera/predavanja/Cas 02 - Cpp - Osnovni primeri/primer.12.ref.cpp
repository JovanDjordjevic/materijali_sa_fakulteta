#include <iostream>
using namespace std;

// 	Upotreba pokazivaca u C-u...
//		- za pristupanje dinamicki alociranom prostoru
//		- za prenosenje velikih objekata po adresi, bez kopiranja
//	U drugom slucaju imamo dva ozbiljna problema:
//		- sintaksa je necitka, jer moramo da koristimo operatore 
//		  dereferisanja (*) u telu funkcija i uzimanja adrese (&)
//		  pri pozivanju
//		- u deifniciji funkcije koja bi trebalo samo da cita objekata
//		  moze gresko doci do njegovog menjanja, sto prevodilac nije
//		  u mogucnosti da prepozna kao gresku.
//		- u telu funkcije argument moze da se promeni tako da pokazuje
//		  na neki drugi objekat, sto otezava proveravanje korektnosti

void swap( int* ap, int* bp )
{
	int t = *ap;
	*ap = *bp;
	*bp = t;
}

// 	C++ uvodi koncept "reference" da bi se resio problem sintakse.
//	"Referenca" je zapravo "prenos objekta po adresi (imenu)"
//	i implementira se (prevodi na masinski jezik) identicno kao
//	rad sa pokazivacima, ali uz prihvatljiviju sintaksu:
//		- pri deklarisanju funkcije oznacavamo da se argument 
//		  prenosi po referenci:
//				...( int &a )
//		- nisu potrebne dodatne operacije referisanja i dereferisanja
//		  pri upotrebi argumenta u telu funkcije i pozivanju funkcija
//		- argument u telu funkcije ne moze da se promeni tako da 
//		  se odnosi na drugi objekat, vec stalno referise originalnu
//		  vrednost argumenta

//	Da, C++ omogucava da napisemo vise funkcija sa istim imenom,
//	sve dok se na osovu broja ili tipova argumenata moze nedvosmisleno
//	utvrditi kada bi koja funkcija trebalo da se poziva. Ako prevodilac
//	ne moze da se odluci, prijavice gresku.
//	To se naziva "viseznacnost imena", ili doslovno prevodjeno, 
//	"preopterecivanje imena" (engl. name overloading).

void swap( int& a, int& b )
{
	int t = a;
	a = b;
	b = t;
}

int main()
{
	int a(5), b=7;

	cout << "a = " << a << ", b = " << b << endl;
	swap( &a, &b );
	cout << "a = " << a << ", b = " << b << endl;
	swap( a, b );
	cout << "a = " << a << ", b = " << b << endl;

	return 0;
}

