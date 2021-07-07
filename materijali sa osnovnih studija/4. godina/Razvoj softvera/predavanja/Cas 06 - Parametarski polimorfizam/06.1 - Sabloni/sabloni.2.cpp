#include <iostream>
using namespace std;

// zamena makroa inline funkcijom
//  - jednako efikasno kao makro
//  - bezbedna sintaksa
//  - manja fleksibilnost - samo za jedan tip podataka
inline int max1( int x, int y )
{
	return x > y ? x : y;
}

int main()
{
	cout << max1(1,2) << endl;
	cout << max1(2.45, 2.54) << endl;

	int a=2;
	// koliko ce biti a?
	cout << max1(a++,a--) << endl;
	cout << a << endl;
}
