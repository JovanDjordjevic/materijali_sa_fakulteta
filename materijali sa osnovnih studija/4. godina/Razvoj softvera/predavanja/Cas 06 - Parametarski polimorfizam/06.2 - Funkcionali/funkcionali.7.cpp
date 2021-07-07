#include <iostream>
#include <vector>
#include <list>

// izdvajanje obilaska pomocu iteratora
// veliki deo standardne bibilioteke pociva na tom pristupu

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

template<typename T, typename Iterator>
unsigned prebroj( Iterator beg, Iterator end, bool(*uslov)(T) )
{
	unsigned n=0;
	for( Iterator i=beg; i!=end; i++ )
		if( uslov( *i ))
			n++;
	return n;
}

template<typename T, typename TK>
unsigned prebroj( const TK& kolekcija , bool(*uslov)(T) )
{
	return prebroj( kolekcija.begin(), kolekcija.end(), uslov );
}

int main()
{
	 vector<int> niz;
	for( unsigned i=0; i<100; i++ )
		niz.push_back(i);
		
	cout << prebroj(niz,neparan) << endl;
	cout << prebroj(niz.begin(), niz.end(),neparan) << endl;
	cout << prebroj(niz.begin()+20, niz.begin()+35,neparan) << endl;

	// ovo ne moze sa svim kolekcijama, jer ne mogu svi iteratori da idu unazad
	//takodje + i - na iteratore ne moraju uvek nuzno da budu validni, posebno za strukture podataka koje u
	//memoriji nisu linearne, npr vektor jeste linearan, ali lista nije
	cout << prebroj(niz.begin()+20, niz.end()-25,neparan) << endl;
		
	return 0;
}
