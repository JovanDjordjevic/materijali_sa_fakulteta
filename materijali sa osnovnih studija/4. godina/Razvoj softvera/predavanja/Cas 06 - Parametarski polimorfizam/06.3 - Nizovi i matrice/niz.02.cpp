#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// nizovi sa i bez provere indeksa

//---------------------------------------------------------------
class ProveraIndeksa {
public:
	static void Provera( unsigned indeks, unsigned opseg ){
		if( indeks >= opseg )
			throw out_of_range("Indeks van opsega");
	}
};

class BezProvereIndeksa{
public:
	static void Provera( unsigned indeks, unsigned opseg ){}
};

//---------------------------------------------------------------
template<typename T,typename ProveravacIndeksa>
class Niz : public vector<T>
{
public:
	Niz( unsigned n )
		: vector<T>(n)
		{}
			
	T& operator[]( unsigned i )
	{
		ProveravacIndeksa::Provera( i, vector<T>::size() );
		return vector<T>::operator[](i);
	}

	const T& operator[]( unsigned i ) const
	{
		ProveravacIndeksa::Provera( i, vector<T>::size() );
		return vector<T>::operator[](i);
	}
};

//---------------------------------------------------------------
int main()
{
	try	{
		Niz<int,ProveraIndeksa> niz(10);
		for( unsigned i=0; i<niz.size(); i++ )
			niz[i] = i*i;
		for( unsigned i=0; i<=niz.size(); i++ )
			cout << i << " : " << niz[i] << endl;
				
		cout << niz[9999999] << endl;
		
	}catch( exception& e ){
		cerr << "*** GRESKA: " << e.what() << endl;
	}

	return 0;
}
