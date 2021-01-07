/*******************************
*  Gramatika je:
*  e -> e+t
*	|t
*  t -> t*f
*	|f
*  f => (e)
*	|BROJ
*  Moramo se obavezno osloboditi leve rekurzije
*  pravila	skupovi izbora
*  e -> te'	{ BROJ , ( }
*  e'->	+te'	{ + }
*	|eps	{ ) , EOI }
*  t -> ft'	{ ( , BROJ }
*  t'-> *ft'	{ * }
*	|eps	{ + , ) , EOI }
*  f -> (e)	{ ( }
*	|BROJ	{ BROJ }
*  Skupove izbora smo dobili za sva pravila koja nisu epsilon
*  na osnovu skupova PRVI, a za epsilon pravila na osnovu
*  skupova SLEDI
*
*  Zadatak 3.c hocemo da prosirimo tako da program ispisuje
*  taj aritmeticki izraz, ali u postfiksnoj notaciji
*  Npr 2+3 ispisuje 2 3 +
*  Npr 2+3*4 ispisuje 2 3 4 * +
*  Akcije koji dodajemo pravilima cemo pisati u okviru pravila
*  jer cemo time precizirati kada se akcije izvrsavaju u samom pravilu
*  pravila			skupovi izbora
*  e -> te'			{ BROJ , ( }
*  e'->	+t{print(+)}e'		{ + }
*	|eps			{ ) , EOI }
*  t -> ft'			{ ( , BROJ }
*  t'-> *f{print(*)}t'		{ * }
*	|eps			{ + , ) , EOI }
*  f -> (e)			{ ( }
*	|BROJ{print(BROJ.v)}	{ BROJ }
*******************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tokeni.h"

void greska(char* m){
	fprintf(stderr,"%s\n",m);
	exit(EXIT_FAILURE);
}

//#define ISPIS 

int yylval;

extern int yylex();

int e();
int ep();
int t();
int tp();
int f();

int preduvid;

int main(){
	int rezultat;
	preduvid = yylex();
	rezultat = e();
	if(preduvid !=EOI)
		greska("Previse tokena na ulazu!\n");
	
	printf("\n\nIspravan algebarski izraz i ima vrednost %d!\n", rezultat);
	return 0;
}

int e(){
	if(preduvid == BROJ || preduvid == OZ ){
#ifdef ISPIS
		printf("e => t ep\n");
#endif
		return t() + ep();
	}
	else{
		greska("Sintaksna greska: Ocekivalo se BROJ ili (\n");
	}	
	return 0;
}

int ep(){
	if(preduvid == PLUS){
#ifdef ISPIS
		printf("ep => + t ep\n");
#endif
		preduvid = yylex();
		int pom = t();
		printf("+ ");
		return pom +	ep();
	}
	else if( preduvid == ZZ || preduvid == EOI){
#ifdef ISPIS
		printf("ep => eps\n");
#endif		
		return 0;
	}
	else greska("Sintaksna greska: Ocekivalo se EOI ili ) ili +\n");

	return 0;
}


int t(){
	if(preduvid == OZ || preduvid == BROJ){
#ifdef ISPIS
		printf("t => f tp\n");
#endif		
		return f() * tp();
	}
	else greska("Sintaksna greska: Ocekivalo se ( ili BROJ\n");	

	return 0;
}

int tp(){
	if(preduvid == PUTA){
#ifdef ISPIS
		printf("tp => * f tp\n");
#endif		
		int pom;
		preduvid = yylex();
		 pom=f();
		printf("* ");
		return pom *	tp();
	}
	else if( preduvid == PLUS || preduvid ==ZZ || preduvid == EOI){
#ifdef ISPIS
		printf("tp =>eps\n");
#endif		
		return 1;
	}
	else greska("Sintaksna greska: Ocekivalo se *, +, ), EOI");
	return 0;	
}

int f(){
	if(preduvid == OZ){
#ifdef ISPIS
		printf("f => ( e )\n");
#endif		
		int pom;
		preduvid = yylex();
		pom = e();
		if(preduvid != ZZ)
			greska("Sintaksna greska: Ocekivalo se )\n");
	
		preduvid = yylex();
		return pom;
	}
	else
		if(preduvid == BROJ){
#ifdef ISPIS
		printf("f => BROJ\n");
#endif			
			preduvid = yylex();
			printf("%d ",yylval);
			return yylval;
		}
		else greska("Sintaksna greska: Ocekivalo se ( ili BROJ\n");
		return 0;	
}
