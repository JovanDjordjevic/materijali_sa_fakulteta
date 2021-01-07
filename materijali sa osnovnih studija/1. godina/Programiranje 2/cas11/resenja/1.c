#include<stdio.h>
#include<stdlib.h>

typedef struct _cvor
{
  int vrednost;
  struct _cvor* sledeci;
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
 
  return novi;
}

Cvor* pronadji_poslednji(Cvor* lista)
{
  if(lista == NULL)
    return NULL;
  
  if(lista->sledeci == lista)
    return lista;
  
  Cvor* prvi = lista;
  
  while(lista->sledeci != prvi)
    lista = lista->sledeci;
  
  return lista;
}

void dodaj_na_kraj(Cvor** lista, int broj)
{
  Cvor* poslednji = pronadji_poslednji(*lista);
  if(poslednji == NULL)
  {
    *lista = napravi_cvor(broj);
	(*lista)->sledeci = *lista;
  }
  else
  {
    Cvor* novi = napravi_cvor(broj);
    poslednji->sledeci = novi;
	novi->sledeci = *lista;
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
	while(1)
	{
		/*
		Pomeramo se tako da je element koji treba ispisati
		prvi sledeci clan liste
		idemo do k-1 iz razloga sto brojanje krece od trenutnog elementa i jos -1 
		jer hocemo da stanemo ispred elementa kog treba obrisati --> odatle k-2
		*/
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
			free(tmp);
			//Pomeramo se na prvi sledeci element od kog se brojanje nastavlja
			lista = lista->sledeci;
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
	
//ispisi(lista);
plesaci(lista, k);

//listu ne treba oslobadjati je smo je vec oslobodili unutar poziva funkcije plesaci.
return 0;
}