#include <iostream>
using namespace std;

// podrazumevane vrednosti parametara sablona
//ovo nam omogucava da pri konstrukciji objekat ove klase, ne moramo da 
//eksplicitno navodimo tip u <> (vidi u mainu ispod)
template <class T = int>
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

//iance i ovakve stvaris u dozvoljene, mzoemo imati vise tipova, 
//a neki mozda mogu biti jednaki kao neki drugi itd itd
//template<typename T1, typename T2 = T1> ...

int main()
{
	Tacka<> t(1,2,3);
	cout << t << endl;
	cout << Tacka<>(1.2, 1.3, 1.4) << endl;
	cout << Tacka<float>(1.2, 1.3, 1.4) << endl;
}
