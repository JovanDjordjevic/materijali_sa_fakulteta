 #include<stdio.h>
 #include "stabla.h"
 
 int identitet(Cvor* s1, Cvor* s2)
 {
	if(s1 == NULL && s2 == NULL)
		return 1;
	else if(s1 == NULL || s2 == NULL || s1->vrednost != s2->vrednost)
		return 0;
	else
		return identitet(s1->levo, s2->levo) && identitet(s1->desno, s2->desno);
 }
 
 int main(){
		
	Cvor* s1 = NULL;
	Cvor* s2 = NULL;

	int broj;
	
	//Ucitavanje prvog stabla
	while(1){
		scanf("%d", &broj);
		if(broj == 0)
			break;
		dodaj_u_stablo(&s1, broj);
	}
	
	//Ucitavanje drugog stabla
	while(1){
		scanf("%d", &broj);
		if(broj == 0)
			break;
		dodaj_u_stablo(&s2, broj);
	}
	
	if(identitet(s1, s2))
		printf("Da\n");
	else
		printf("Ne\n");
		
	//Oslobadjanje
	oslobodi_stablo(s1);
	oslobodi_stablo(s2);
	
	return 0;
 }