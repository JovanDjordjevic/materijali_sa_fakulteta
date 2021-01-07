 #include<stdio.h>
 #include "stabla.h"
 #include <limits.h>
 
 int broj_cvorova(Cvor* koren)
 {
	if(koren == NULL)
		return 0;
	return broj_cvorova(koren->levo) + broj_cvorova(koren->desno) + 1;
 }
 
 int broj_listova(Cvor* koren)
 {
	if(koren == NULL)
		return 0;
	
	if(koren->levo == NULL && koren->desno == NULL)
		return 1;
		
	return broj_listova(koren->levo) + broj_listova(koren->desno);
 }
 
 void pozitivni_listovi(Cvor* koren)
 {
	if(koren == NULL)
		return;
	
	if(koren->levo == NULL && koren->desno == NULL)
	{
		//dosli smo do lista
		if(koren->vrednost > 0)
			printf("%d ", koren->vrednost);
		return;
	}
	
	pozitivni_listovi(koren->levo);
	pozitivni_listovi(koren->desno);
 }
 
 int zbir_cvorova(Cvor* koren)
 {
	if(koren == NULL)
		return 0;
	return koren->vrednost + zbir_cvorova(koren->levo) + zbir_cvorova(koren->desno);
 }
 
 int najveci_element(Cvor* koren)
 {
	if(koren == NULL)
		return INT_MIN;
		
	if(koren->desno == NULL)
		return koren->vrednost;
	
	return najveci_element(koren->desno);
 }
 
 int dubina_stabla(Cvor* koren)
 {
	if(koren == NULL)
		return 0;
	
	int dubina_levo = dubina_stabla(koren->levo);
	int dubina_desno = dubina_stabla(koren->desno);
	
	if(dubina_desno > dubina_levo)
		return dubina_desno + 1;
	else
		return dubina_levo + 1;
 }
 
 int cvorovi_na_nivou_i(Cvor* koren, int i)
 {
	if(koren == NULL)
		return 0;
		
	if(i == 0)
		return 1;	
	else //nivo < i
		return cvorovi_na_nivou_i(koren->levo, i-1) + cvorovi_na_nivou_i(koren->desno, i-1);
		
 }
 
 void stampaj_cvorove_na_nivou_i(Cvor* koren, int i)
 {
	if(koren == NULL)
		return;
		
	if(i == 0)
		printf("%d ", koren->vrednost);	
	else //nivo < i
	{	
		stampaj_cvorove_na_nivou_i(koren->levo, i-1); 
		stampaj_cvorove_na_nivou_i(koren->desno, i-1);
	}	
 }
 
 int najveci_na_nivou_i(Cvor* koren, int i)
 {
	if(koren == NULL)
		return INT_MIN;
	
	if(i == 0)
		return koren->vrednost;
	else
	{
		int max_levo = najveci_na_nivou_i(koren->levo, i-1);
		int max_desno = najveci_na_nivou_i(koren->desno, i-1);
		
		return max_desno > max_levo ? max_desno : max_levo;
	}
 }
 
 int zbir_na_nivou_i(Cvor* koren, int i)
 {
	if(koren == NULL)
		return 0;
	
	if(i == 0)
		return koren->vrednost;
	
	return zbir_na_nivou_i(koren->levo, i-1) + zbir_na_nivou_i(koren->desno, i-1);
 
 }
 
 int zbir_manjih_od_x(Cvor* koren, int x)
 {
	if(koren == NULL)
		return 0;
	if(koren->vrednost <= x)
		return zbir_manjih_od_x(koren->levo, x) + zbir_manjih_od_x(koren->desno, x) + koren->vrednost;
	else
		return zbir_manjih_od_x(koren->levo, x);
 }
 
 int main(int argc, char* argv[])
 {
 
	if(argc != 3)
		greska();
		
	int i = atoi(argv[1]);
	if(i < 0)
		greska();
		
	int x = atoi(argv[2]);
 
	Cvor* s = NULL;
	ucitaj_stablo(&s, stdin);
	
	ispisi_stablo(s, stdout);
	printf("\n");
	
	printf("Broj cvorova: %d\n", broj_cvorova(s));
	printf("Broj listova: %d\n", broj_listova(s));
	printf("Pozitivni listovi: ");
	pozitivni_listovi(s); 
	printf("\n");
	printf("Zbir cvorova: %d\n", zbir_cvorova(s));
	printf("Najveci element: %d\n", najveci_element(s));
	printf("Dubina stabla: %d\n", dubina_stabla(s));
	printf("Broj cvorova na %d. nivou: %d\n", i, cvorovi_na_nivou_i(s, i));
	printf("Elementi na nivou i: ");
	stampaj_cvorove_na_nivou_i(s, i);
	printf("\n");
	printf("Najveci na nivou i: %d\n", najveci_na_nivou_i(s,i));
	printf("Zbir na nivou i: %d\n", zbir_na_nivou_i(s, i));
	printf("Zbir <= od %d: %d\n",x, zbir_manjih_od_x(s, x));
	
	oslobodi_stablo(s); 
 return 0;
 }