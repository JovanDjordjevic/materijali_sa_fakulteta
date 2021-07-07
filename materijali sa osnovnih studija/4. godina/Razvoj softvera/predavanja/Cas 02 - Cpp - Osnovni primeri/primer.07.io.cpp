#include <iostream>
#include <fstream>
using namespace std;

// Datoteke...

int main()
{
	cout << "Upisi dva cela broja" << endl;
	int a,b;
	cin >> a >> b;

	ofstream fdat("dat.txt");
	fdat << a << " + " << b << " = " << a + b << endl;
	
	ifstream dat2("dat.txt");
	char c1,c2;
	int c;
	dat2 >> a >> c1 >> b >> c2 >> c;
	cout << a << c1 << b << c2 << c << endl;
}

