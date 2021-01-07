#include<stdio.h>

#include "stabla.h"

int proveri_susede(Cvor* trenutni, int vrednost_roditelja)
{
	if(trenutni == NULL)
		return 0;
	
	int vrednost_levo = 0;
	int vrednost_desno = 0;
	
	if(trenutni->levo != NULL)
		vrednost_levo = trenutni->levo->vrednost;
		
	if(trenutni->desno != NULL)
		vrednost_desno = trenutni->desno->vrednost;
		
	return trenutni->vrednost == (vrednost_desno + vrednost_levo + vrednost_roditelja);
}

int jednaki_susedima(Cvor* koren)
{
	if(koren == NULL)
		return 0;
	
	int tr_rez = 0;
	if(proveri_susede(koren->levo, koren->vrednost))
		tr_rez++;
	if(proveri_susede(koren->desno, koren->vrednost))
		tr_rez++;
		
	return tr_rez + jednaki_susedima(koren->levo) + jednaki_susedima(koren->desno);
}

int main()
{
	Cvor* stablo = NULL;
	ucitaj_stablo(&stablo, stdin);

	printf("%d\n", jednaki_susedima(stablo) + proveri_susede(stablo, 0));
	
	oslobodi_stablo(stablo);
return 0;
}