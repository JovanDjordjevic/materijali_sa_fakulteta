#include <iostream>
#include <fstream>
using namespace std;

// 	Stanje toka se ocitava metodom rdstate(), koji vraca
//	ios_base::iostate, kao disjunkciju stanja:
//		ios::goodbit
//		ios::eofbit
//		ios::failbit
//		ios::badbit
//	Takodje, konkretniji metodi proveravaju samo neke bitove:
//		good() = rdstate() & ios::goodbit
//		eof() = rdstate() & ios::eofbit
//		fail() = rdstate() & ( ios::failbit | ios::badbit )
//		bad() = rdstate() & ios::badbit
//	Stanje moze da se menja metodom 
//		void clear (iostate state = goodbit)
//	Takodje, automatska konverzija toka u logicku vrednost
//	vraca good().
//
//	Promena stanja se preporucuje samo u slucaju kada operacija ne uspe
//	zbog pogresnog formata zapisa (fail) ali ne i u slucaju BAD.

int main()
{
	cout << "Upisi dva cela broja" << endl;
	int a,b;
	cin >> a >> b;

	if( !cin ){
		if( cin.eof() )
			cerr << "Kraj!" << endl;
		else
			cerr << "Greska!" << endl;
		return 1;
	}
	
	cout << a << " + " << b << " = " << a + b << endl;
}
