#include <iostream>
#include <vector>

// prebrojavanje neparnih podataka u nizu, klasican pristup

using namespace std;

unsigned prebrojNeparne( const vector<int>& niz )
{
	unsigned n=0;
	for( int x : niz  )
		if( x % 2 )
			n++;
	return n;
}

int main()
{
	vector<int> niz;
	for( unsigned i=0; i<100; i++ )
		niz.push_back(i);
		
	cout << prebrojNeparne(niz) << endl;
		
	return 0;
}
