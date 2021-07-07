#include <iostream>
using namespace std;

// zamena funkcije sablonom funkcije 
//  - jednako efikasno kao makro
//  - bezbedna sintaksa
//  - ista ili cak veca fleksibilnost

//u tempalte mozemo koristiti i class i typename kljucne reci, to dodje na isto

//sablonske funkcije se prevode tek kada se u kodu naidje na neku konkretnu njihovu upotrebu
//ovde npr, u mainu kad pozivamo max1(1,2) prevesce se ova funkcija sa ubacenim parametrima
//int i int (sto ima smisla pa tp prolazi), i tako redom za svaki poziv
template <class T>
inline const T& max1( const T& x, const T& y )
{
	return x > y ? x : y;
} 

//inace ako imamo sablonsku funkciju i obocnu funkciju koje se zovu isto, 
//uvek ce se prednost u pozivanju dati obicnoj funkciji
//ako ta funkcija ne moze da se iskoristi, onda ce se traziti prvi sablon koji moze
//i to prvos e trazi neka konkretana specijalizacija sablona, a onda ako nista od toga ne uspe
//prvi sablon u koji moze da se uklopi sa najmanje konverzija (?)
//na kraju ako nista od toga ne uspe, koristi se opsti oblik sablona

int main()
{
	cout << max1(1,2) << endl;
	cout << max1(2.45, 2.54) << endl;

	// primer neispravnog implicitnog instanciranja
	// cout << max1(1, 2.5) << endl; 
	// mora eksplicitno:
	cout << max1<double>(1, 2.5) << endl; 
	cout << max1<char>( 'a', 53.2 ) << endl;

	int a=2;
	// koliko ce biti a?
	cout << max1(a++,a--) << endl;
	cout << a << endl;
}
