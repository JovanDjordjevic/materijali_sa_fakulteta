 #include<stdio.h>
 #include<stdlib.h>
 
 #define MAX_BROJ 15
 
 void greska()
 {
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
 }
 
 typedef enum
 {
	BROJ,
	OPERACIJA
 } TipCvora;
 
 typedef struct _Cvor
 {
	int vrednost;
	char operator;
	TipCvora tip;
	struct _Cvor* levo;
	struct _Cvor* desno;
 } Cvor;
 
 Cvor* ucitaj(FILE* f)
 {
	char tmp[MAX_BROJ];
	
	if(fscanf(f, "%s", tmp) == EOF)
		return NULL;
		
	Cvor* novi = malloc(sizeof(Cvor));
	if(tmp[0] == '+' || tmp[0] == '-' || tmp[0] == '*' || tmp[0] == '/')
	{
		if(tmp[1] != '\0')
			greska();
			
		novi->operator = tmp[0];
		novi->tip = OPERACIJA;
		novi->levo = ucitaj(f);
		novi->desno = ucitaj(f);
	}
	else
	{
		int broj = atoi(tmp);
		novi->vrednost = broj;
		novi->tip = BROJ;
		novi->levo = NULL;
		novi->desno = NULL;
	}
	return novi;
 }
 
 void ispisi(Cvor* koren)
 {
	if(koren == NULL)
		return;
		
	if(koren->tip == BROJ)
		printf("%d", koren->vrednost);
	else
	{
		printf("(");
		ispisi(koren->levo);
		printf(")%c(", koren->operator);
		ispisi(koren->desno);
		printf(")");
	}
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
 
 float vrednost(Cvor* koren)
 {
	if(koren == NULL)
		return 0;
	
	if(koren->tip == BROJ)
		return koren->vrednost;

	float vrednost_levo = vrednost(koren->levo);
	float vrednost_desno = vrednost(koren->desno);
	
	switch(koren->operator)
	{
		case '+':
			return vrednost_levo + vrednost_desno;
			break;
		case '-':
			return vrednost_levo - vrednost_desno;
			break;
		case '*':
			return vrednost_levo * vrednost_desno;
			break;
		case '/':
			if(vrednost_desno != 0)
				return vrednost_levo/vrednost_desno;
			else
				greska();
		default:
			greska();
	}
	
}
 
 int main()
 {
	FILE* ulaz = fopen("izraz.txt", "r");
	if(ulaz == NULL)
		greska();
		
	Cvor* stablo = ucitaj(ulaz);
	ispisi(stablo);
	
	printf("Vrednost izraza: %.2f\n", vrednost(stablo));
	
	fclose(ulaz);
	oslobodi(stablo);
	return 0;
 }