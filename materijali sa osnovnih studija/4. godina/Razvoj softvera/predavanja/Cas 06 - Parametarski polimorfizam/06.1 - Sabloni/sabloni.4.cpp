#include <iostream>
#include <cstring>
using namespace std;

// zamena funkcije sablonom funkcije 
//  - jednako efikasno kao makro
//  - bezbedna sintaksa
//  - ista ili cak veca fleksibilnost
template <class T>
inline T max1( T x, T y )
{
	return x > y ? x : y;
}

// eksplicitna specijalizacija za const char*
template<>
inline const char* max1( const char* x, const char* y ) {
	cout << "poziv sablona" << endl;
	return strcmp(x,y)>0 ? x : y;
}

// naredna funkcija nije isto sto i prethodna, zato sto ona nije sablon
inline const char* max1( const char* x, const char* y ) {
	cout << "poziv funkcije" << endl;
	return x>y ? x : y;
}

// parametar sablona moze da bude i konstanta 
// koja se vezuje u vreme prevodjenja
template<int N>
inline bool veceOd( int x )
{
	return x > N;
}


int main()
{
	cout << max1(1,2) << endl;
	cout << max1(2.45, 2.54) << endl;

	// primer neispravnog implicitnog instanciranja
	// cout << max1(1, 2.5) << endl; 
	// mora eksplicitno:
	cout << max1<double>(1, 2.5) << endl; 
	cout << max1<char>( 'a', 53.2 ) << endl;

	// ovde se poziva sablon za T=const char* 
	cout << max1<>("aaa","bbb") << endl;

	// ovde se poziva funkcija
	cout << max1("aaa","bbb") << endl;

	// ovde se proverava da li je 10 vece od 5
	// 5 se vezuje u vreme prevodjenja, a 10 u vreme izvrsavanja
    // (u ovom slucaju se i 10 vezuje u vreme prevodjenja zbog 'inline')
	cout << veceOd<5>(10) << endl;
}
