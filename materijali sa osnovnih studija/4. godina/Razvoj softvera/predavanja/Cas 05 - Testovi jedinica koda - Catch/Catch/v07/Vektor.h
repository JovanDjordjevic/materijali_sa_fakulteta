#ifndef VEKTOR_H_
#define VEKTOR_H_

#include <iostream>

class Vektor
{
public:
	Vektor()
		: X_(0), Y_(0), Z_(0)
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

	friend std::istream& operator>>( std::istream& ostr, Vektor& v );
};

std::ostream& operator<<( std::ostream& ostr, const Vektor& v );
std::istream& operator>>( std::istream& istr, Vektor& v );

#endif // #ifndef VEKTOR_H_
