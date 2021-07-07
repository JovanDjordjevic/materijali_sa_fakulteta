#include <iostream>
#include <vector>

// upotreba funkcijskog parametra

using namespace std;

bool neparan( int n )
{ 
	return n%2;
}

//kada koristimo funkciu kao parametar, pisemo  povratni_tip(*ime_parametra)(tipovi argumenata)
unsigned prebroj( const vector<int>& niz, bool(*uslov)(int) )
{
	unsigned n=0;
	for( int x : niz  )
		if( uslov( x ))
			n++;
	return n;
}

int main()
{
	vector<int> niz;
	for( unsigned i=0; i<100; i++ )
		niz.push_back(i);

	//ovde navodimo ime konkretne funkcije koja treba da se koristi	
	cout << prebroj(niz, neparan) << endl;
		
	return 0;
}
