#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

//---------------------------------------------------------------
//  niz sa proveravanjem opsega

template<typename T>
class Niz : public vector<T>
{
public:
	Niz()
		: vector<T>()
	{}
		
	Niz( unsigned int sz )
		: vector<T>( sz )
	{}
		
	T& operator[]( unsigned i )
	{
		if( i >= vector<T>::size() )
			throw out_of_range("Indeks van opsega");
		return vector<T>::operator[](i);
	}

	const T& operator[]( unsigned i ) const
	{
		if( i >= vector<T>::size() )
			throw out_of_range("Indeks van opsega");
		return vector<T>::operator[](i);
	}
};

//---------------------------------------------------------------
int main()
{
	try	{
		Niz<int> niz(20);

		for( unsigned i=0; i<niz.size(); i++ )
			niz[i] = i*i;
		for( unsigned i=0; i<=niz.size(); i++ )
			cout << i << " : " << niz[i] << endl;
		
	}catch( exception& e ){
		cerr << "*** GRESKA: " << e.what() << endl;
	}

	return 0;
}
