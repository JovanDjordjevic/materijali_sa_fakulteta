#include <iostream>
using namespace std;

// 	Promenljiva moze da se definise kao referenca:
//		- mora da se inicijalizuje
//		- ne moze da se promeni tako da predstavlja drugi objekat.

int main()
{
	int a(100), b(200);
	int& c(a);
	
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

	a = 101;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
	
	c = 102;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

	b = 201;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
	
	c = b;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
	
	c = 100;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

	b = 202;
	cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

	return 0;
}

