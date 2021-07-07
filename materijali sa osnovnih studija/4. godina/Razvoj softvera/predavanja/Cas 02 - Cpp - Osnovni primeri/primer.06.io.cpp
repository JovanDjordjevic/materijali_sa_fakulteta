#include <iostream>
#include <fstream>
using namespace std;

//	Za rad sa datotekama se koristi <fstream>.
//	Otvaranje datoteke se vrsi konstrukcijom objekta
//	ili metodom open(path,flags), a zatvaranje
//	unistavanjem objekta ili metodom close().

//	Izlazni datotecni tok je "ofstream".
//	Konstruktori su:
//		ofstream()
//		ofstream( const char* filename, 
//				  ios_base::openmode mode = ios_base::out)
//	Rezim se odredjuje kao disjunkcija vrednosti:
//		ios::in		=	otvaranje za citanje
//		ios::out	=	otvaranje za pisanje
//		ios::binary	=	binarni rezim (podrazumeva se tekstualni)
//		ios::ate	=	pozicioniranje na kraj fajla pri otvaranju
//		ios::app	=	pozicioniranje na kraj fajla pre svakog pisanja
//		ios::trunc	=	odbacivanje prethodnog sadrzaja
//	Nije dopustena kombinacija app|trunc.
//	Pre C++11 nije bila dopustena kombinacija app|in.

//	Ulazni datotecni tok je "ifstream".
//	Konstruktori su:
//		ifstream()
//		ifstream( const char* filename, 
//				  ios_base::openmode mode = ios_base::in)
//	Nije dopusteno trunc bez out.
//	Pre C++11 nije bio dopusten app, a od tada nije dopusteno app|trunc.

int main()
{
	cout << "Upisi dva cela broja" << endl;
	int a,b;
	cin >> a >> b;

	ofstream fdat("dat.txt");
	fdat << a << " + " << b << " = " << a + b << endl;
}

