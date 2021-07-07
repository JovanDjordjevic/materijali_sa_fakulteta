#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// dodati testovi

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
void test2()
{
	Matrica<int,2,ProveraIndeksa> m(10,5);
	for(unsigned i=0;i<m.size(1);i++)
		for(unsigned j=0; j<m.size(2); j++ )
			m[i][j] = i*100 + j;

	for(unsigned i=0;i<m.size(1);i++){
		for(unsigned j=0; j<m.size(2); j++ )
			cout << m[i][j] << ' ';
		cout << endl;
	}
}

void test3()
{
	Matrica<int,3,ProveraIndeksa> m(4,5,6);
	for(unsigned i=0;i<m.size(1);i++)
		for(unsigned j=0; j<m.size(2); j++ )
			for(unsigned k=0; k<m.size(3); k++ )
				m[i][j][k] = (i+1)*100 + (j+1)*10 + (k+1);

	for(unsigned i=0;i<m.size(1);i++){
		for(unsigned j=0; j<m.size(2); j++ ){
			for(unsigned k=0; k<m.size(3); k++ )
				cout << m[i][j][k] << ' ';
			cout << endl;
		}
		cout << "------------------" << endl;
	}
}

void test3a()
{
	Matrica<int,3,ProveraIndeksa> m(4,5,6);
	for(unsigned i=0;i<m.size(1);i++){
		Matrica<int,2,ProveraIndeksa> m2(5,6);
		for(unsigned k=0;k<m2.size(1);k++)
			for(unsigned j=0; j<m2.size(2); j++ )
				m2[k][j] = (i+1)*1000 + k*100 + j;
		m[i] = m2;
	}

	for(unsigned i=0;i<m.size(1);i++){
		for(unsigned j=0; j<m.size(2); j++ ){
			for(unsigned k=0; k<m.size(3); k++ )
				cout << m[i][j][k] << ' ';
			cout << endl;
		}
		cout << "------------------" << endl;
	}
}


int main()
{
	try	{
		test2();		
		test3();		
		test3a();		
	}catch( exception& e ){
		cerr << "*** GRESKA: " << e.what() << endl;
	}

	return 0;
}
