#include <iostream>

using namespace std;

class PrimerUnikata
{
public:
	...
};



// primeri upotrebe
void test1()
{
	cout << "test1::pocetak" << endl;
...
	cout << "test1::kraj" << endl;
}

void test2()
{
	cout << "test2::pocetak" << endl;
...
	cout << "test2::kraj" << endl;
}

int main()
{
	cout << "main::pocetak" << endl;
...

	test1();
	test2();

	cout << "main::kraj" << endl;

	return 0;	
}

