#include<stdio.h>
#include<stdlib.h>

typedef struct _cvor
{
  int vrednost;
  struct _cvor* sledeci;
  struct _cvor* prethodni;
}Cvor;

void greska()
{
  fprintf(stderr, "-1\n");
  exit(EXIT_FAILURE);
}

Cvor* napravi_cvor(int broj)
{
  Cvor* novi = malloc(sizeof(Cvor*));
  if(novi == NULL)
    greska();
  
  novi->vrednost = broj;
  novi->sledeci = NULL;
  novi->prethodni = NULL;
 
  return novi;
}

void dodaj_na_kraj(Cvor** lista, int broj)
{
  if(*lista == NULL)
  {
    *lista = napravi_cvor(broj);
	(*lista)->sledeci = *lista;
	(*lista)->prethodni = *lista;
  }
  else
  {
    Cvor* novi = napravi_cvor(broj);
	novi->prethodni = (*lista)->prethodni;
   (*lista)->prethodni->sledeci = novi;
   novi->sledeci = *lista;
   (*lista)->prethodni = novi;
  }
}

void ispisi(Cvor* lista)
{
	Cvor* prvi = lista;
		while(lista){
			printf("%d ", lista->vrednost);
			
			if(lista->sledeci == prvi)
				break;

			lista = lista->sledeci;
		}
	printf("\n");
}

void plesaci(Cvor* lista, int k)
{
	if(k == 1)
	{
		ispisi(lista);
		return;
	}
	int i;
	int smer = 1; //1->desno 0->levo
	while(1)
	{
		if(smer) //Pomeramo se za k mesta u desno i stampamo plesaca
		{
			for(i=0; i<k-2; i++)
				lista = lista->sledeci;
			
			if(lista == lista->sledeci)
			{
				/*
				Ako je u pitanju poslednji clan liste, onda ispisujemo njegovu vrednost i izlazimo iz funkcije
				*/
				printf("%d\n", lista->vrednost);
				free(lista);
				return;
			}
			else
			{
				/*
				Ako nije poslednji, onda ispisujemo vrednost sledeceg elementa
				i brisemo ga iz liste:
				*/
				printf("%d ", lista->sledeci->vrednost);
				Cvor* tmp = lista->sledeci;
				lista->sledeci = lista->sledeci->sledeci;
				lista->sledeci->prethodni = lista;
				free(tmp);
			}
			smer = 0; //Postavljamo da se sledeci put ide u levo
		}
		else //Pomeramo se za k mesta u levo i stampamo plesaca
		{
			for(i=0; i<k-2; i++)
				lista = lista->prethodni;
			
			if(lista == lista->sledeci)
			{
				/*
				Ako je u pitanju poslednji clan liste, onda ispisujemo njegovu vrednost i izlazimo iz funkcije
				*/
				printf("%d\n", lista->vrednost);
				free(lista);
				return;
			}
			else
			{
				/*
				Ako nije poslednji, onda ispisujemo vrednost prethodnog elementa
				i brisemo ga iz liste:
				*/
				printf("%d ", lista->prethodni->vrednost);
				Cvor* tmp = lista->prethodni;
				lista->prethodni = lista->prethodni->prethodni;
				lista->prethodni->sledeci = lista;
				free(tmp);
			}
			smer = 1; //Postavljamo da se sledeci put ide u desno;
		}
	}
}

int main(){

int n, k;
scanf("%d%d", &n, &k);
if(n < 1 || k < 1)
	greska();
Cvor* lista = NULL;

int i;
for(i=1; i<=n; i++)
	dodaj_na_kraj(&lista, i);
	
ispisi(lista);
plesaci(lista, k);

//listu ne treba oslobadjati je smo je vec oslobodili unutar poziva funkcije plesaci.
return 0;
}