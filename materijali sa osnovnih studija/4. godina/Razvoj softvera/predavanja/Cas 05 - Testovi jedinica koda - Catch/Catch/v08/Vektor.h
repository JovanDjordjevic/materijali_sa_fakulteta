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
		: X_(x), Y_(y), Z_(z)
		{}
		
	double getX() const
		{ return X_; }

	double getY() const
		{ return Y_; }
		
	double getZ() const
		{ return Z_; }
		
	bool operator==( const Vektor& v ) const
	{
		return getX() == v.getX()
			&& getY() == v.getY()
			&& getZ() == v.getZ();			
	}
	
	bool operator!=( const Vektor& v ) const
		{ return !(*this == v); }
		
private:
	double X_, Y_, Z_;
	
	friend istream& operator>>( istream& ostr, Vektor& v );
};

ostream& operator<<( ostream& ostr, const Vektor& v );
istream& operator>>( istream& istr, Vektor& v );

#endif // #ifndef VEKTOR_H_
