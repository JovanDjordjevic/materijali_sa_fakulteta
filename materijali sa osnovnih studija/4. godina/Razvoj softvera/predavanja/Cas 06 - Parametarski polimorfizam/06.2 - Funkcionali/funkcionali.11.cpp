#include <iostream>
#include <vector>

// Dodajemo parametrizovan funkcional.

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

bool veciOd5( int n )
{ 
	return n > 5;
}

//--------------------------
class Neparan
{
public:
	bool operator()( int n )
		{ return n%2; }
};
//--------------------------

//--------------------------
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
//--------------------------

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

	cout << prebroj(niz,VeciOd(10)) << endl;

	for( int i=0; i<100; i+=5 )
		cout << i << " : " << prebroj(niz,VeciOd(i)) << endl;
	
	return 0;
}
