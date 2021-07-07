#include <iostream>
using namespace std;

// pocetni primer, upotreba makroa
#define max1(x,y) ((x) > (y) ? (x) : (y))

int main()
{
	cout << max1(1,2) << endl;
	cout << max1(2.45, 2.54) << endl;

	int a=2;
	// koliko ce biti a?
	//konkretno u ovom primeru na kraju ce biti a=1 i to ce se ispisati.
	// ++ i -- rade nakons to se izvrsi ceo izraz, a u nasem slucaju ono sot se desava je
	// kada se makro ubaci u ovaj red dobijamo  2 > 2 ? , ta provera je false, i onda se desi
	// (y), dakle ukupno imamo a++ a-- a--,  i onda to bude 1
	cout << max1(a++,a--) << endl;
	cout << a << endl;
}
