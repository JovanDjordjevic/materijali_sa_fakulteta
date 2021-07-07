#include <iostream>
#include <fstream>
using namespace std;

//	Za konzolni ulaz i izlaz se koriste objekti "cout" i "cin".
//	Oba prepoznaju tipove argumenata u fazi prevodjenja.
//	Citanje niski se zavrsava prvim praznim prostorom.

int main()
{
	cout << "Upisi dva cela broja" << endl;
	int a,b;
	cin >> a >> b;
	cout << a << " + " << b << " = " << a + b << endl;
}

