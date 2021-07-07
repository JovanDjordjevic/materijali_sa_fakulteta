#include <iostream>
#include <vector>

// Funkcionali su problematicni, zato sto se pisu udaljeno od mesta 
// na kome se koriste, cak i onda kada se trivijalno definisu i kada
// smo sigurni da ih nikada vise necemo koristiti.
// Zbog toga C++ 11 uvodi pojednostavljenu "inline" sintaksu funkcionala,
// koja omogucava njihovo pisanje na mestu upotrebe, a prevod je prakticno
// ekvivalentan. To su tzv. "lambda funkcije".
// (mora da se prevodi za C++11)

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

bool veciOd5( int n )
{ 
	return n > 5;
}

class Neparan
{
public:
	bool operator()( int n )
		{ return n%2; }
};

class VeciOd
{
public:
	VeciOd( int n )
		: _N(n)
	{}
	
	bool operator()( int n )
		{ return n > _N; }
		
private:
	int _N;
};

template<int n>
bool veciOd( int x )
{
	return x > n;
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
	cout << prebroj(niz,veciOd5) << endl;
	cout << prebroj(niz,Neparan()) << endl;

	cout << prebroj(niz,veciOd<5>) << endl;
	
	for( int i=0; i<100; i+=5 )
		cout << i << " : " << prebroj(niz,VeciOd(i)) << endl;
	
	// Ako je u pitanju jednostavna funkcija, tako se i prevodi.
	// Ovaj primer je ekvivalentan funkciji "neparan".
	//      [] - pocetak funkcije, ime nije potrebno zato sto je necemo drugde koristiti
	//      (int n) - argumenti funkcije
	//      {...} - telo funkcije
	cout << prebroj( niz, [](int n){ return n%2; }) << endl;
	
	// Ako je u pitanju nesto slozenije, pa zelimo da funkciji prenesemo neke
	// promenljive koje su vidljive na mestu definisanja, onda je zapravo u pitanju
	// funkcional.
	// Ovaj primer je ekvivalentan funkcionalu "VeciOd".
	// [i] - naglasava da funkcional cuva parametar "i"
	//       kao da smo napisali:
	//			class VeciOd {
	//				int i;
	//				VeciOd(int _i) : i(_i) {}
	//				...
	//			}
	//		i zatim napravili objekat sa "VeciOd(i)"
	for( int i=0; i<100; i+=5 )
		cout << i << " : " 
			 << prebroj( niz, [i](int n){ return n>i; } ) << endl;
	
	return 0;
}
