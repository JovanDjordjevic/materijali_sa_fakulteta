#include <iostream>
#include <vector>

// uopstavanje obilaska kolekcije pomocu iteratora
// ovaj korak je nepotreban kada se koristi ranged-for
using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

template<typename T>
unsigned prebroj( const vector<T>& niz, bool(*uslov)(T) )
{
	unsigned n=0;
	for( const T& x : niz )
		if( uslov( x ))
			n++;
	return n;
}

int main()
{
	vector<int> niz;
	for( unsigned i=0; i<100; i++ )
		niz.push_back(i);
		
	cout << prebroj(niz,neparan) << endl;
		
	return 0;
}
