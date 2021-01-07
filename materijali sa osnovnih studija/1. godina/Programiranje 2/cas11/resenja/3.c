#include<stdio.h>
#include"stabla.h"

int main()
{
//Inicijalizujemo prazno stablo
Cvor* s = NULL;

//Ucitavamo elemente stabla sa standardnog ulaza
ucitaj_stablo(&s, stdin);

//Ispisujemo elemente stabla na standardni izlaz na sva tri nacina
printf("Infiksni ispis: ");
ispisi_stablo_infiksno(s);
printf("\n");

printf("Prefiksni ispis: ");
ispisi_stablo_prefiksno(s);
printf("\n");

printf("Postfiksni ispis: ");
ispisi_stablo_postfiksno(s);
printf("\n");

//Ispis na standardni izlaz u infiksnom poretku
//ispisi_stablo(s, stdout);

//Oslobadjamo memoriju
oslobodi_stablo(s);

return 0;
}
