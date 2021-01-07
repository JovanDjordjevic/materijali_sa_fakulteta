 #include<stdio.h>
 #include "stabla.h"
 
 Cvor* pretrazi_stablo(Cvor* koren, int broj)
{
	if(koren == NULL)
		return NULL;
	
	if(koren->vrednost == broj)
		return koren;
	else if(broj < koren->vrednost)
		return pretrazi_stablo(koren->levo, broj);
	else
		return pretrazi_stablo(koren->desno, broj);
}

Cvor* pronadji_najmanji(Cvor* koren)
{
	if(koren == NULL)
		return NULL;
	if(koren->levo == NULL)
		return koren;
	return pronadji_najmanji(koren->levo);
}

Cvor* pronadji_najveci(Cvor* koren)
{
	if(koren == NULL)
		return NULL;
	if(koren->desno == NULL)
		return koren;
	return pronadji_najveci(koren->desno);
}

void obrisi_element(Cvor** koren, int broj)
{
	if(*koren == NULL)
		return;
	
	if(broj < (*koren)->vrednost)
	{
		obrisi_element(&(*koren)->levo, broj);
		return;
	}
	else if(broj > (*koren)->vrednost)
	{
		obrisi_element(&(*koren)->desno, broj);
		return;
	}
	else{
		//treba da se obrise koren:
		
		//1. slucaj -> nema decu
		if((*koren)->levo == NULL && (*koren)->desno == NULL)
		{
			free(*koren);
			*koren = NULL;
		} 
		else if((*koren)->levo == NULL) //2. slucaj: ima samo desno dete
		{
			Cvor* tmp = *koren;
			*koren = (*koren)->desno;
			free(tmp);
		}else if((*koren)->desno == NULL) //3. slucaj: ima samo levo dete
		{
			Cvor* tmp = *koren;
			*koren = (*koren)->levo;
			free(tmp);
		}else{ //4. slucaj: ima oba deteta
			//pronadjemo sledbenika
			Cvor* sl = pronadji_najmanji((*koren)->desno);
			
			//zamenimo im vrednosti
			(*koren)->vrednost = sl->vrednost;
			sl->vrednost = broj;
			
			//pozovemo brisanje elementa u desnom podstablu
			obrisi_element(&(*koren)->desno, broj);
		}
	}
}

 
 int main()
 {
        //Obavezna inicijalizacija stabla
	Cvor* s = NULL;
	
	ucitaj_stablo(&s, stdin);
	Cvor * min = pronadji_najmanji(s);
	
	ispisi_stablo(s, stdout);
	printf("\n");
	
	if(min != NULL)
		printf("Najmanji clan: %d\n", min->vrednost);
	
	obrisi_element(&s, 5);
	ispisi_stablo(s, stdout);
	printf("\n");
	
	oslobodi_stablo(s);
 return 0;
 }