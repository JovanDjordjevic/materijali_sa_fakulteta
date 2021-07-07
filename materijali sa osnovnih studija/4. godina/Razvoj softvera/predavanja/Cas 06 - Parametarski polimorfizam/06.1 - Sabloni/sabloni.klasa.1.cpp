#include <iostream>
using namespace std;

// primer jednostavne konkretne klase

class Tacka
{
public:
	int x,y,z;
	Tacka(int x0, int y0, int z0)
		: x(x0), y(y0), z(z0)
		{}
};

ostream& operator<<( ostream& ostr, const Tacka& t )
{
	ostr << "(" << t.x << "," << t.y << "," << t.z << ")";
	return ostr;
}

int main()
{
	Tacka t(1,2,3);
	cout << t << endl;
	cout << Tacka(1.2, 1.3, 1.4) << endl;
}
