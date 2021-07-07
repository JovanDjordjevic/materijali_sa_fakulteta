#include <iostream>
#include <vector>
#include <list>

// uopstavanje tipa kolekcije, zato sto se i druge kolekcije 
// obilaze na isti nacin pomocu iteratora
// i ovaj korak je nepotreban kada se koristi ranged-for
using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

template<typename T, typename TK>
unsigned prebroj( const TK& kolekcija , bool(*uslov)(T) )
{
	unsigned n=0;
	for( const T& x : kolekcija )
		if( uslov( x ))
			n++;
	
    // ako se koriste iteratori, mora ovako:
	// kljucna rec 'typename' je neophodna po standardu da bi se 
	// prevodiocu naglasilo da je TK::const_iterator ime tipa
//	typename TK::const_iterator
//		i = kolekcija.begin(),
//		e = kolekcija.end();
//	for( ; i!=e; i++ )
//		if( uslov( *i ))
//			n++;

	return n;
}

int main()
{
	// vector<int> niz;
	list<int> niz;
	for( unsigned i=0; i<100; i++ )
		niz.push_back(i);
		
	cout << prebroj(niz,neparan) << endl;
		
	return 0;
}
