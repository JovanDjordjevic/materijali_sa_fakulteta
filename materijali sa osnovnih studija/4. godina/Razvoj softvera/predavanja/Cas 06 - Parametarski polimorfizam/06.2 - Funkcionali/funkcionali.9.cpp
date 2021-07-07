#include <iostream>
#include <vector>

// dodajemo novu funkciju koju koristimo kao predikat

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

bool veciOd5( int n )
{ 
	return n > 5;
}

bool veciOd3( double n )
{ 
	return n > 5;
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
unsigned prebroj( const TK& kolekcija, Predikat uslov )
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
	
	cout << prebroj(niz,veciOd5) << endl;
	cout << prebroj(niz.begin(), niz.end(),veciOd5) << endl;
	cout << prebroj(niz.begin()+20, niz.begin()+35,veciOd5) << endl;

	// Primetimo da ovde mozemo da koristimo i funkciju koja ne ocekuje ceo broj.
	// To ne bi moglo da je "uslov" ostao sa fiksnim tipom.
	cout << prebroj(niz,veciOd3) << endl;
	
	return 0;
}
