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
		Matrica<int,2,ProveraIndeksa> m(10,5);
		for(unsigned i=0;i<m.size(1);i++)
			for(unsigned j=0; j<m.size(2); j++ )
				m[i][j] = i*100 + j;

		for(unsigned i=0;i<m.size(1);i++){
			for(unsigned j=0; j<m.size(2); j++ )
				cout << m[i][j] << ' ';
			cout << endl;
		}
		cout << endl;
				
		cout << m[5][10] << endl;
		
	}catch( exception& e ){
		cerr << "*** GRESKA: " << e.what() << endl;
	}

	return 0;
}
