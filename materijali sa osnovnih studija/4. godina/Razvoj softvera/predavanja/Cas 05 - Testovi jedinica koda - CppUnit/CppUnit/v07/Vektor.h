#ifndef VEKTOR_H_
#define VEKTOR_H_

class Vektor
{
public:
	Vektor( double x, double y, double z )
		: _X(x), _Y(y), _Z(z)
		{}
		
	double getX() const
		{ return _X; }

	double getY() const
		{ return _Y; }
		
	double getZ() const
		{ return _Z; }
		
private:
	double _X, _Y, _Z;
};

#endif /* VEKTOR_H_ */
