#include <iostream>
using namespace std;

// 	Enkapsulacija.
//	Javni interfejs i privatna implementacija.
//	Da bi operatori za citanje i pisanje mogli da pristupaju
//	podacima klase, proglasavaju se za prijatelje.

//--------------------------------------------------
class Tacka
{
public:
	Tacka( double x, double y )
		: X_(x), Y_(y)
		{}
		
private:
	double X_;
	double Y_;
	
	friend ostream& operator<<( ostream&, const Tacka& );
	friend istream& operator>>( istream&, Tacka& );
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

