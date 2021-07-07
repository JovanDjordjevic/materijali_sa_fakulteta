#include <iostream>
using namespace std;

// uopstavanje razlicitih klasa jednim sablonom klase

template <class T>
class Tacka
{
public:
	T x,y,z;
	Tacka(T x0, T y0, T z0)
		: x(x0), y(y0), z(z0)
		{}
};

template <class T>
ostream& operator<<( ostream& ostr, const Tacka<T>& t )
{
	ostr << "(" << t.x << "," << t.y << "," << t.z << ")";
	return ostr;
}

int main()
{	
	//kod sablona klasa, uvek moramo sami da navedemo konretan tip T koji
	//se u njima koristi (za sablone funkcija nismo morali, tj automatski su se
	//odredjivali tipovi)
	Tacka<int> t(1,2,3);
	cout << t << endl;
	cout << Tacka<int>(1.2, 1.3, 1.4) << endl;
	cout << Tacka<float>(1.2, 1.3, 1.4) << endl;
}
