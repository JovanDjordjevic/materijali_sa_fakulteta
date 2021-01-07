#include<stdio.h>

#include "stabla.h"

/* 
Implementacija reda preko liste
Osnovne operacije sa redom: dodaj_na_kraj i skini_sa_pocetka
Red cemo realizovati preko liste, tako sto cemo pamtiti pokazivac 
na prvi element i pokazivac na poslednji element
*/

/*
Jedan element reda je opisan odgovarajucim podacima 
i pokazivacem na sledeci clan reda.
U ovom slucaju podaci su:
	-cvor stabla (cvorovi se u red smestaju u redosledu ispisa po nivoima)
	-njegov nivo (samo zbog ispisa koji se trazi u zadatku)
*/
typedef struct _CvorReda
{
	Cvor* cvor_stabla;
	int nivo;
	struct _CvorReda* sledeci;
} CvorReda;

/* Funkcija koja pravi novi cvor u redu na osnovu prosledjenih podataka */
CvorReda* napravi_cvor_reda(Cvor* cvor_stabla, int nivo)
{
	CvorReda* novi = malloc(sizeof(CvorReda));
	if(novi == NULL)
		greska();
	
	novi->cvor_stabla = cvor_stabla;
	novi->nivo = nivo;
	novi->sledeci = NULL;
	
	return novi;
}

/* Funkcija koja dodaje novi element na kraj reda */
void dodaj_na_kraj_reda(CvorReda **pocetak, CvorReda** kraj, Cvor* cvor_stabla, int nivo)
{
	CvorReda* novi = napravi_cvor_reda(cvor_stabla, nivo);
	
	if(*pocetak == NULL) //red je prazan --> oba pokazivaca postavljamo na novi cvor
	{
		*pocetak = novi;
		*kraj = novi;
	}
	else //dodajemo na kraj i pomeramo pokazivac kraja
	{
		(*kraj)->sledeci = novi;
		*kraj = novi;
	}
}

/* Funkcija koja brise element koji se nalazi na pocetku reda */
int skini_sa_pocetka(CvorReda** pocetak, CvorReda** kraj)
{
	if(*pocetak == NULL)
		return 0;
	
	if(*pocetak == *kraj) //red ima samo jedan element
	{
		free(*pocetak);
		*pocetak = NULL;
		*kraj = NULL;
	}
	else{
		CvorReda* tmp = *pocetak;
		*pocetak = (*pocetak)->sledeci;
		free(tmp);
	}
	
	return 1;
}

/* 
Funkcija koja ispisuje stablo po nivoima, 
a kao pomocnu strukturu podataka koristi red.

Princip: 
   1. Dodaj koren u red 
   2. Dok god je red neprazan:
      Uzmi prvi clan u redu i:
	      2.1 Dodaj u red njegovu decu (ako ih ima)
		  2.2 Ispisi vrednost tekuceg clana
		  2.3 Obrisi tekuci clan iz reda
		  
Primer:
	Stablo: 10 5 15 3 2 4 30 12 14 13
				10
		5				15
	3				12		30
2		4			  14
					13

-Dodaj 10 [10]
-Dodaj 5 i 15 [10 5 15]
-Skini 10 i ispisi ga [5 15]
-Dodaj 3 (dete od 5) [5 15 3]
-Skini 5 i ispisi ga [15 3]
-Dodaj 12 i 30 (decu od 15) [15 3 12 30]
-Skini 15 i ispisi ga [3 12 30]
-Dodaj 2 i 4 (decu od 3) [3 12 30 2 4]
-Skini 3 i ispisi ga [12 30 2 4]
...
*/

void ispisi_po_nivoima(Cvor* stablo)
{
	if(stablo == NULL)
		return;
	
	CvorReda* prvi = NULL;
	CvorReda* poslednji = NULL;
	dodaj_na_kraj_reda(&prvi, &poslednji, stablo, 0);
	int trenutni_nivo = -1;
	while(prvi != NULL) //dok god je red neprazan
	{
		/*Ako je doslo do promene nivoa, ispisujemo na kom smo trenutno nivou*/
		if(prvi->nivo != trenutni_nivo)
		{
			trenutni_nivo = prvi->nivo;
			printf("\n%d.nivo: ", trenutni_nivo);
		}
	
		if(prvi->cvor_stabla->levo)
			dodaj_na_kraj_reda(&prvi, &poslednji, prvi->cvor_stabla->levo, prvi->nivo + 1);

		if(prvi->cvor_stabla->desno)
			dodaj_na_kraj_reda(&prvi, &poslednji, prvi->cvor_stabla->desno, prvi->nivo + 1);
	
		printf("%d ", prvi->cvor_stabla->vrednost);
		
		if(!skini_sa_pocetka(&prvi, &poslednji))
			greska();
	}
	
	printf("\n");
}

int main()
{
	Cvor* stablo = NULL;
	ucitaj_stablo(&stablo, stdin);
	ispisi_po_nivoima(stablo);
	oslobodi_stablo(stablo);
        return 0;
}