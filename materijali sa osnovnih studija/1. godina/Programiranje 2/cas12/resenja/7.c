 #include<stdio.h>
 #include<stdlib.h>
 
 void greska()
 {
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
 }
 
 typedef struct _Cvor{
	char slovo;
	int broj_ponavljanja;
	struct _Cvor* levo;
	struct _Cvor* desno;
 } Cvor;
 
 Cvor* napravi_cvor(char c)
 {
	Cvor* novi = malloc(sizeof(Cvor));
	if(novi == NULL)
		greska();
		
	novi->slovo = c;
	novi->broj_ponavljanja = 0;
	novi->levo = NULL;
	novi->desno = NULL;
	
	return novi;
 }
 
 void dodaj_u_stablo(Cvor** koren, char c)
 {
	if(*koren == NULL)
	{
		*koren = napravi_cvor(c);
		return;
	}
	
	if(c < (*koren)->slovo)
		dodaj_u_stablo(&(*koren)->levo, c);
	else if(c > (*koren)->slovo)
		dodaj_u_stablo(&(*koren)->desno, c);
	else	
		(*koren)->broj_ponavljanja++;
 }
 
 Cvor* napravi_stablo_iz_fajla(FILE* f)
 {
	Cvor* s = NULL;
	char c;
	
	while((c = fgetc(f)) != EOF)
		dodaj_u_stablo(&s, c);
		
	return s;
 }
 
 Cvor* maks_ponavljanja(Cvor* koren)
 {
	if(koren == NULL)
		return NULL;
		
	Cvor* maks_levo = maks_ponavljanja(koren->levo);
	Cvor* maks_desno = maks_ponavljanja(koren->desno);
	
	if(maks_levo == NULL && maks_desno == NULL)
		return koren;
	
	Cvor* maks_levo_desno;
	if(maks_levo == NULL)
		maks_levo_desno = maks_desno;
	else if(maks_desno == NULL)
		maks_levo_desno = maks_levo;
	else
		maks_levo_desno = maks_levo->broj_ponavljanja > maks_desno->broj_ponavljanja ? maks_levo : maks_desno;
		
	return maks_levo_desno->broj_ponavljanja > koren->broj_ponavljanja ? maks_levo_desno : koren;
 }
 
 void oslobodi(Cvor* koren)
 {
	if(koren)
	{
		oslobodi(koren->levo);
		oslobodi(koren->desno);
		free(koren);
	}
 }
 
 int main(){
 
	FILE* ulaz = fopen("karakteri.txt", "r");
	if(ulaz == NULL)
		greska();
 
	Cvor* stablo = napravi_stablo_iz_fajla(ulaz);
	Cvor* maks  = maks_ponavljanja(stablo);
	printf("%c: %d\n", maks->slovo, maks->broj_ponavljanja);
 
	fclose(ulaz);
	oslobodi(stablo);
	
	return 0;
 }