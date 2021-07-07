#ifndef VEKTOR_H_
#define VEKTOR_H_

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
		
private:
	double X_, Y_, Z_;
};

#endif // #ifndef VEKTOR_H_
