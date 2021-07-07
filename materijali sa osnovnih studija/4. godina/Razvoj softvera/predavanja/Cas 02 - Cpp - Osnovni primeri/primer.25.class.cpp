#include <iostream>
using namespace std;

//	U ovom primeru je ilustrovano kako se i kada poziva 
//	koji od metoda iz prethodnog primera.

class tacka;
ostream& operator<<( ostream& ostr, const tacka& a );

class tacka
{
public:
	int x;
	int y;
	
	tacka()
		: x(0), y(0)
	{ 
		cerr << "*konstruktor bez argumenata: " << *this << endl;
	}
	
	tacka( int x0, int y0 )
		: x(x0), y(y0)
	{ 
		cerr << "*konstruktor: " << *this << endl;
	}
	
	tacka( const tacka& t )
		: x(t.x), y(t.y)
	{ 
		cerr << "*konstruktor kopije: " << *this << endl;
	}
	
	~tacka()
	{ 
		cerr << "*destruktor: " << *this << endl;
	}

	tacka& operator=( const tacka& t )
	{ 
		x = t.x;
		y = t.y;
		cerr << "*operator dodeljivanja: " << *this << endl;
		return *this;
	}	
};

ostream& operator<<( ostream& ostr, const tacka& a ) 
{
	ostr << "(" << a.x << "," << a.y << ")";
	return ostr;
}

istream& operator>>( istream& istr, tacka& a )
{
	char c1,c2,c3;
	istr >> c1 >> a.x >> c2 >> a.y >> c3;
	if( c1!='(' || c2!=',' || c3!=')' )
		istr.setstate( ios::failbit );
	return istr;
}

int main()
{
	tacka t1(1,2);
	tacka t2(3,4);
	tacka niz_automatski[2];
	tacka t3(t1);

	for( int i=0; i<3; i++ ){
		tacka t4 = t2;
	}
	t3 = t2;

	tacka* niz_dinamicki = new tacka[3];
	delete [] niz_dinamicki;

	//	Naredni primer je namerno pogresan, da bi se videlo da se pri 
	//	upotrebi "delete" destruktor ne poziva za svaki od elemenata niza
	// 	(!!! u nekim slucajevima program cak i puca, 
	//	na primer MINGW/G++ prevodilac)
	niz_dinamicki = new tacka[2];
	delete niz_dinamicki;
	
	return 0;
}