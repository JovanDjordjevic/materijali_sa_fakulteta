#ifndef VEKTOR_H_
#define VEKTOR_H_

#include <iostream>
using namespace std;

class Vektor
{
public:
	Vektor()
		{}
		
	Vektor( double x, double y, double z )
		: _X(x), _Y(y), _Z(z)
		{}
		
	double getX() const
		{ return _X; }

	double getY() const
		{ return _Y; }
		
	double getZ() const
		{ return _Z; }
		
	bool operator==( const Vektor& v ) const
	{
		return getX() == v.getX()
			&& getY() == v.getY()
			&& getZ() == v.getZ();			
	}
	
	bool operator!=( const Vektor& v ) const
		{ return !(*this == v); }
		
private:
	double _X, _Y, _Z;
	
	friend istream& operator>>( istream& ostr, Vektor& v );
};

ostream& operator<<( ostream& ostr, const Vektor& v );
istream& operator>>( istream& istr, Vektor& v );

#endif /* VEKTOR_H_ */
