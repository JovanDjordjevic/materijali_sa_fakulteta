#include <iostream>

using namespace std;

class PrimerUnikata
{
public:
	// metod koji vraca primerak unikata 
	static PrimerUnikata& Primerak()
	{
		//Staticka lokalna promenljiva je promenljiva koja se zapravo vodi kao globalna,
		//ali joj je ime definisano lokalno, tako da je niko van naseg koda ne vidi
		//i ono sot je vazno je da se ona nicijalizuje samo pri prvom pozivu ove funkcije
		//Pri svakom narednom pozivu se nece inicijalizovati, koristice se uvek sita vrednost
		
		//Ovo je bolje nego Alternativa 1 zatos to se fizicki prostor za ovaj podatak odredjuje
		//prilikom povezivanja, tj ucitavanja programa u memoriju, njegova konstrukcija se izvrsava
		//pri prvom pozivu ove funkcije, a svi ovakvi objekti se automatski unistavaju pri izlasku
		//iz programa (u obrnutom redosledu od redosleda pravljenja)
		static PrimerUnikata primerak {};
		return primerak;		
		
		//	Alternativa 1
		//	-----------------
		//	Nije idealno resenje, zato sto se objekat nikada ne unistava.
		//	Ipak, u nekim slucajevima redosled unistavanja medjusobno 
		//	referisanih unikata moze da napravi probleme, pa tada 
		//	meze biti opravdana odluka da neki unikat ostane neobrisan.
/*
		static PrimerUnikata* p = new PrimerUnikata();
		return *p;
*/
		
		//	Alternativa 2
		//	-----------------
		//	Iako izgleda da je ovo resenje ekvivalentno prethodnom,
		//	ono nije dobro iz vise razloga.
		//	Najvaznije je da ovaj kod nije bezbedan po niti.
		//	Ako dve niti "istovremeno" zatraze jos uvek neinicijalizovan
		//	primerak unikata, moze da dodje do dvostruke konstrukcije.
		//	Pored toga, kao i u alt.1, postoji curenje memorije.
		//	Dalje, resenje ne moze samo u zaglavlje, jer mora da se 
		//	definise podatak "_Primerak".
/*
		//	Pretpostavlja se dodavanje privatnog podatka klase:
		//		private:
		//			static T* _Primerak = 0;
		if( !_Primerak )
			_Primerak = new PrimerUnikata();
		return *_Primerak;
*/
	}

	// primer metoda, samo broji upotrebe
	// kako bi bilo jasno da se sve upotrebe odnose na isti objekat
	void Metod()
	{
		cout << ++Brojac_ << endl;
	}
	
private:
	// brojac poziva metoda Metod()
	int Brojac_;
	
	// Konstruktor mora da bude privatan,
	//	da niko ne bi mogao da pravi dodatne objekte ove klase.
	PrimerUnikata() 
		: Brojac_(0)
		{}
		
	//	Naredne deklaracije onemogucavaju upotrebu 
	//	konstruktora kopije i operatora dodeljivanja.
	//	(moguce od C++11)
	PrimerUnikata( const PrimerUnikata& ) = delete;
	PrimerUnikata& operator=( const PrimerUnikata& ) = delete;
	
	//	U starijim verzijama je bilo potrebno da se to radi 
	//	malo komplikovanije:
	//	1. deklarisu se privatno, pa niko van klase ne moze da ih koristi
	//	2. ne implementiraju se, pa ne mogu da se koriste ni u klasi
};



// primeri upotrebe
void test1()
{
	cout << "test1::pocetak" << endl; 
	PrimerUnikata::Primerak().Metod();
	cout << "test1::kraj" << endl;
}

void test2()
{
	cout << "test2::pocetak" << endl;
	PrimerUnikata& s = PrimerUnikata::Primerak();
	s.Metod();
	s.Metod();
	test1();
	cout << "test2::kraj" << endl;
}

int main()
{
	cout << "main::pocetak" << endl;
	PrimerUnikata::Primerak().Metod();
	test1();
	test2();
	PrimerUnikata::Primerak().Metod();
	cout << "main::kraj" << endl;
	return 0;	
}

