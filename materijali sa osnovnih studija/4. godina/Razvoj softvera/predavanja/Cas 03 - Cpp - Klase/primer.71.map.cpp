#include <iostream>
#include <map>
#include <string>
using namespace std;

// map

int main()
{
	map<string,string> katalog;
	while(1){
		string kljuc, vrednost;
		cin >> kljuc;
		if( kljuc == "kraj" )
			break;
		cin >> vrednost;
		
		// VAZNO! Kada proveravamo da li kljuc postoji, 
		// onda ne smemo da koristimo
		//		katalog[kljuc] 
		// zato sto se tako automatski dodaje novi par 
		//		(kluc, podrazumevana vrednost)
		
		if( katalog.find(kljuc) != katalog.end() )
			cout << "Vec postoji kljuc " << kljuc << endl;
		else
			katalog[kljuc] = vrednost;
		
	}
	
	cout << "Katalog:" << endl;
	for( map<string,string>::iterator i = katalog.begin(); i!=katalog.end(); i++ )
		cout << i->first << " : " << i->second << endl;

	for( auto par: katalog )
		cout << par.first << " : " << par.second << endl;
		
	return 0;
}

