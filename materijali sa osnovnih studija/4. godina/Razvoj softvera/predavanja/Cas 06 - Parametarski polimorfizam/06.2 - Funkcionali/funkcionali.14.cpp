#include <iostream>
#include <vector>

// Cesto imamo na raspolaganju funkciju koja je binarna
// a zelimo da je upotrebimo za definisanje unarne funkcije.
// Na primer, ako imamo "veciOd(x,y)" i zelimo da fiksiramo "y".
// Osim lambda funkcijama, to moze da se uradi i posebnim funkcionalom,
// koji 'pamti' i funkciju i argument.

using namespace std;

bool veciOd( int n, int m )
{ 
	return n > m;
}

// Funkcional Bind_2_2 pamti binarnu funkciju i njen 2. argument
template<typename Fn, typename T>
class Bind_2_2
{
public:
	Bind_2_2( Fn fn, T arg2 )
		: _Fn(fn), _Arg2(arg2)
	{}
	
	bool operator()( T n )
		{ return _Fn(n,_Arg2); }
		
private:
	Fn _Fn;
	T _Arg2;
};

// Pravljenje sablonskog funkcionala zahteva eksplicitno navodjenje tipa
// na primer: 
// 		Bind_2_2<bool(*)(int,int),int>(veciOd,5)
// sto bas i nije mnogo zgodno za upotrebu, 
// pa se zato pravi pomocni sablon funkcije, koji automatski raspoznaje upotreblene tipove
template<typename Fn, typename T>
Bind_2_2<Fn,T> bind_2_2( Fn fn, T arg2 )
{
	return Bind_2_2<Fn,T>( fn, arg2 );
}

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
		
	cout << prebroj(niz,Bind_2_2<bool(*)(int,int),int>(veciOd,17)) << endl;
	cout << prebroj(niz,bind_2_2(veciOd,17)) << endl;
	cout << prebroj(niz,bind_2_2([](int x,int y){return x>y;},17)) << endl;
	
	// Standardna biblioteka sadrzi napredniju verziju 
	// funkcionala "bind", koja omogucava da se argumentom opise 
	// koji se argument vezuje.
	
	return 0;
}
