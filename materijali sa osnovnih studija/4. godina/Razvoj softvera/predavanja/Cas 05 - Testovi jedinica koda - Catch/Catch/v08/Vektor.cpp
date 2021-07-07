#include "Vektor.h"

ostream& operator<<( ostream& ostr, const Vektor& v )
{
	ostr << '(' << v.getX() << "," << v.getY() << "," << v.getZ() << ")";	
	return ostr;
}

istream& operator>>( istream& istr, Vektor& v )
{
	double x,y,z;
	char c1,c2,c3,c4;
	istr >> c1 >> x >> c2 >> y >> c3 >> z >> c4;
	if( istr && c1 == '(' && c2 == ',' && c3 == ',' && c4 == ')' ){
		v.X_ = x;
		v.Y_ = y;
		v.Z_ = z;
	}else
		istr.setstate( ios::failbit );
	return istr;
}
