#include <iostream>
using namespace std;

//	Upotreba <iostream> je u nacelu efikasnija
//	nego upotreba <stdio>, zato sto se prepoznavanje tipova 
//	vrsi vec pri prevodjenju.
//
//	Ipak, kod nekih verzija prevodilaca postoje neki faktori
//	usporavanja koji to mogu da obrnu:
//		- Pri upotrebi endl se prazne baferi, sto moze
//		  da osetno uspori rad u odnosu na upotrebu '\n'
//		- Zbog kompatibilnosti sa bibliotekom <stdio>, upotreba tokova 
//		  se interno uskladjuje sa upotrebom printf, sto dovodi 
//		  do dodatnih usporenja.
//		  Ako se u programu ne koristi <stdio>, onda to moze da se 
//		  iskljuci pozivom:  std::ios::sync_with_stdio(false)

unsigned const limit = 100000;

void test1()
{
	for( unsigned i=0; i<limit; i++ )
		printf( "%d\n", i );	
}

void test2()
{
	for( unsigned i=0; i<limit; i++ )
		cout << i << endl;
}

void test3()
{
	for( unsigned i=0; i<limit; i++ )
		cout << i << '\n';
}

int main() {
	cerr << "test1" << endl;
	test1();
	cerr << "test2" << endl;
	test2();
	cerr << "test3" << endl;
	test3();
	cerr << "test3 a" << endl;
	test3();
	std::ios::sync_with_stdio(false);	
	cerr << "end" << endl;
}

