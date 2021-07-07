#include <iostream>
using namespace std;

// 	Klasa Tacka. 
//	Slicno kao prosle nedelje, samo su koordinate sada tipa double.

//--------------------------------------------------
class Tacka
{
public:
	Tacka( double x, double y )
		: X_(x), Y_(y)
		{}
		
	double X_;
	double Y_;
};

//--------------------------------------------------
ostream& operator<<( ostream& ostr, const Tacka& t )
{
	ostr << "(" << t.X_ << "," << t.Y_ << ")";
	return ostr;
}

istream& operator>>( istream& istr, Tacka& a )
{
	char c1,c2,c3;
	istr >> c1 >> a.X_ >> c2 >> a.Y_ >> c3;
	if( c1!='(' || c2!=',' || c3!=')' )
		istr.setstate( ios::failbit );
	return istr;
}

//--------------------------------------------------
int main()
{
	Tacka t(20,15);
	cout << t << endl;
	return 0;
}