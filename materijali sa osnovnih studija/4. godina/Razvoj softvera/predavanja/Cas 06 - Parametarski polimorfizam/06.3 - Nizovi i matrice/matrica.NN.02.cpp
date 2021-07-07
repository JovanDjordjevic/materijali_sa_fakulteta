#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// nizovi i matrice sa proverom indeksa
// 'matrice' sa vecim brojem dimenzija

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
	T& operator[]( unsigned i )
	{
		ProveravacIndeksa::Provera( i, size() );
		return vector<T>::operator[](i);
	}

	const T& operator[]( unsigned i ) const
	{
		ProveravacIndeksa::Provera( i, size() );
		return vector<T>::operator[](i);
	}
	
	using vector<T>::size;
};

//---------------------------------------------------------------
template<typename T, unsigned Dim, typename ProveravacIndeksa>
class Matrica
{
public:
	typedef Matrica<T,Dim-1,ProveravacIndeksa> tElementa;
	
	Matrica()
	{}

	Matrica( unsigned dims[] ) {
		PostaviVelicinu( dims );
	}
	
	Matrica(unsigned d1, 
			unsigned d2=0,
			unsigned d3=0,
			unsigned d4=0,
			unsigned d5=0,
			unsigned d6=0,
			unsigned d7=0,
			unsigned d8=0
			)
	{
		ProveravacIndeksa::Provera( Dim-1, 8 );
		unsigned d[] = { d1, d2, d3, d4, d5, d6, d7, d8 };
			PostaviVelicinu(d);
	}
	
	void PostaviVelicinu( unsigned dims[] ) {
		_Elementi.resize(dims[0]);
		for( unsigned i=0; i<dims[0]; i++ )
			_Elementi[i].PostaviVelicinu(dims+1);
	}

	tElementa& operator[]( unsigned d1 ) {
		return _Elementi[d1];
	}
	
	const tElementa& operator[]( unsigned d1 ) const {
		return _Elementi[d1];
	}

	unsigned size( unsigned d ) const {
		if( d==1 )
			return _Elementi.size();
		else 
			return _Elementi[0].size(d-1);
	}

private:
	Niz<tElementa,ProveravacIndeksa> _Elementi;
};

//---------------------------------------------------------------
template<typename T, typename ProveravacIndeksa>
class Matrica<T,1,ProveravacIndeksa>
{
public:
	Matrica()
	{}
	
	void PostaviVelicinu( unsigned dims[] ) {
		_Elementi.resize(dims[0]);
	}

	T& operator[]( unsigned d1 ) {
		return _Elementi[d1];
	}
	
	const T& operator[]( unsigned d1 ) const {
		return _Elementi[d1];
	}

	unsigned size( unsigned d ) const {
		ProveravacIndeksa::Provera( d-1, 1 );
		return _Elementi.size();
	}
	
private:
	Niz<T,ProveravacIndeksa> _Elementi;
};


//---------------------------------------------------------------
int main()
{
	try	{
		Matrica<int,3,ProveraIndeksa> m(10,2,5);
		cout << m.size(1) << endl;
		cout << m.size(2) << endl;
		cout << m.size(3) << endl;
		cout << endl;
		
	}catch( exception& e ){
		cerr << "*** GRESKA: " << e.what() << endl;
	}

	return 0;
}
