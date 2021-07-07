#include <iostream>
using namespace std;

// 	Upotreba pokazivaca u C-u...
//		- za pristupanje dinamicki alociranom prostoru
//		- za prenosenje velikih objekata po adresi, bez kopiranja
//	U drugom slucaju imamo ozbiljne probleme:
//		- sintaksa je necitka, jer moramo da koristimo operatore 
//		  dereferisanja (*) u telu funkcija i uzimanja adrese (&)
//		  pri pozivanju
//		- u deifniciji funkcije koja bi trebalo samo da cita objekata
//		  moze gresko doci do njegovog menjanja, sto prevodilac nije
//		  u mogucnosti da prepozna kao gresku
//		- u telu funkcije argument moze da se promeni tako da pokazuje
//		  na neki drugi objekat, sto otezava proveravanje korektnosti

void swap( int* ap, int* bp )
{
	int t = *ap;
	*ap = *bp;
	*bp = t;
}

int main()
{
	int a(5), b=7;	//	moze i a{8}

	cout << "a = " << a << ", b = " << b << endl;
	swap( &a, &b );
	cout << "a = " << a << ", b = " << b << endl;

	return 0;
}

