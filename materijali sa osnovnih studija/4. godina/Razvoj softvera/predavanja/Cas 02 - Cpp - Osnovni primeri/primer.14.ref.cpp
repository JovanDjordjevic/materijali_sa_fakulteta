#include <iostream>
using namespace std;

// 	Vazan deo price o pokazivacima i referencama su 'const' tipovi,
//	koji oznacavaju objekte koji ne mogu da se menjaju.

//	Veoma je vazno da se svi argumenti funkcija koji se prenose 
//	po adresi (imenu), a koji ne smeju da se menjaju, oznace
//	kao konstantni.

int main()
{
	int a = 100;		//	ceo broj
	const int b = 200;	//	konstantan ceo broj
	
	const int* p = &a;	//	pokazivac na konstantan ceo broj
	*p = 5;				//	GRESKA: ne moze da se menja vrednost broja
	p = &b;				//	pokazivac moze da se menja
	*p = 5;				//	GRESKA: ne moze da se menja vrednost broja
	
	const int& r = a;	//	referenca na konstantan ceo broj
						//	znamo da referenca ne moze da se menja
	r = 3;				//	GRESKA: ne moze da se menja vrednost broja

	return 0;
}

