#include <iostream>
#include <vector>

// Dodajemo i koristimo funkcional
// "Funkcional" je objekat (klasa) koja moze da se koristi
// kao funkcija, tj. ima definisan operator().
// Ovaj operator moze da postoji u razlicitim verzijama,
// za razlicite brojeve i tipove argumenata.

//funkcionai su nam zgodni ako u vreme izvrsavanja pravimo kao nove funkcije
//tj mozda kombinovanjem funkcionala mozemo da izbegnemo da pisemo u kodu
//dosta razlicith funkcija (posebno ako su one jednostavne)

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

bool veciOd5( int n )
{ 
	return n > 5;
}
//--------------
class Neparan
{
public:
	bool operator()( int n )
		{ return n%2; }
};
//-----------------

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
	
	// koristimo objekat funkcional
	Neparan nep;
	cout << prebroj(niz,nep) << endl;
	// koristimo privremeni objekat funkcional
	cout << prebroj(niz.begin(), niz.end(), Neparan() ) << endl;
	cout << prebroj(niz.begin()+20, niz.begin()+35, Neparan()) << endl;
	
	return 0;
}
