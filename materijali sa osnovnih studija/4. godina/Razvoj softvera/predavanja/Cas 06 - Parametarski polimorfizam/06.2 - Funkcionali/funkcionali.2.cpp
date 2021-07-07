#include <iostream>
#include <vector>

// izdvajanje uslova u funkciju

using namespace std;

inline bool neparan( int n )
{ 
	return n % 2;
}

unsigned prebrojNeparne( const vector<int>& niz )
{
	unsigned n=0;
	for( int x : niz  )
		if( neparan( x ))
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
