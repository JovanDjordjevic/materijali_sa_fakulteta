#include <iostream>
#include <vector>
#include <list>

// parametrizujemo tip funkcije sablonom
// tj. parametarskim tipom Predikat
// "Predikat" je unarna logicka funkcija

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

template<typename Iterator, typename Predikat>
unsigned prebroj( Iterator beg, Iterator end, Predikat uslov )
{
	unsigned n=0;
	for( Iterator i=beg; i!=end; i++ )
		if( uslov( *i ))
			n++;
	return n;
}

template<typename TK, typename Predikat>
unsigned prebroj( const TK& kolekcija , Predikat uslov )
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
	cout << prebroj(niz.begin()+20, niz.end()-25,neparan) << endl;
		
	return 0;
}
