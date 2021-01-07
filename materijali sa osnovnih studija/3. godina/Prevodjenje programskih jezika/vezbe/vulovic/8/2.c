/*******************************
*  Gramatika je:
*  e -> e+t
*	|t
*  t -> t*f
*	|f
*  f => (e)
*	|BROJ
*  Moramo se obavezno osloboditi leve rekurzije
*  Ovde smo prepravili prethodni zadatak da pored toga sto
*  preverava da li neki ulaz odgovara aritmetickom izrazu
*  program i racuna vrednos tog izraza
*  Svakom pravilu se dodaje odgovarajuca akcija,
*  i na taj nacin dobijemo shemu prevodjenja
*  pravila	skupovi izbora		akcije
*  e -> te'	{ BROJ , ( }		{e.v = t.v + e'.v}
*  e'->	+te'	{ + }			{e'1.v = t.v + e'2.v}
*	|eps	{ ) , EOI }		{e'.v = 0}
*  t -> ft'	{ ( , BROJ }		{t.v = f.v * t'.v}
*  t'-> *ft'	{ * }			{t'1.v = f.v * t'2.v}
*	|eps	{ + , ) , EOI }		{t'.v = 1}
*  f -> (e)	{ ( }			{f.v = e.v}
*	|BROJ	{ BROJ }			{f.v = BROJ.v}
*  Svim simbolima u stablu smo dodali atribute, tj. vrednosti
*  Primetiti da smo ovde koristili desnu asovijativnost
*  zbog desno rekurzivnih pravila, sto nam nije problem,
*  jer imamo samo sabiranje i mnozenje.
*  Da smo imali i oduzimanje ili deljenje, morali bi da obezbedimo
*  levu asocijativnost iako imamo desno rekurzivna pravila
*  To bi uradili tako sto bi svaki neterminal imao dva atributa
*******************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BROJ 1
#define PLUS 2
#define PUTA 3
#define LZ 4
#define DZ 5
#define EOI 0

#define ISPIS 1 
int preduvid;
int e();
int ep();
int t();
int tp();
int f();

void greska(char* s){
	fprintf(stderr,"%s\n",s);
	exit(EXIT_FAILURE);
}

int yyval;

/*samostalno pisemo leksicki analizator*/
int yylex(){
	char ch =getchar();
	switch(ch){
	case '+':
		return PLUS;
	case '*':
		return PUTA;
	case '(':
		return LZ;
	case ')':
		return DZ;
	case '\n':
	case EOF:
		return EOI;
	} 
	/* ako smo procitali cifru ?*/
	if(isdigit(ch)){
		yyval = ch -'0';
		while(isdigit(ch=getchar()))
			yyval = yyval*10 +ch-'0';
	
		ungetc(ch, stdin);
		return BROJ;
	}
	
	greska("Leksicka greska: nepoznata leksema!");
	return -1;
}


int e(){
	if(preduvid == BROJ || preduvid == LZ){
#ifdef ISPIS
	printf("e --> t ep\n");
#endif
	return t() + ep();
	}
	else greska("Sintaksna greska: Ocekivan je token BROJ ili (.");
	return -1;
}

int ep(){
	if (preduvid== PLUS){
#ifdef ISPIS
	printf("ep --> + t ep\n");
#endif
	preduvid = yylex();
	return t()+ ep();
	}
	else if(preduvid == DZ || preduvid == EOI){
#ifdef ISPIS
		printf("ep --> eps\n");
#endif
		return 0;
	}
	else greska("Sintaksna greska: Ocekivan je token + ili ) ili EOI");
	return -1;
}

int t(){
	if(preduvid == LZ || preduvid == BROJ){
#ifdef ISPIS
	printf("t --> f tp\n");
#endif
	return f() *tp();
	}
	else greska("Sintaksna greska: Ocekivano je LZ ili BROJ.");
	return -1;
}

int tp(){
	if(preduvid == PUTA){
#ifdef ISPIS
	printf("tp --> * f tp\n");
#endif
	preduvid= yylex();
	return f() * tp();
	}
	else if(preduvid == PLUS || preduvid == DZ || preduvid == EOI){
#ifdef ISPIS
	printf("tp --> eps\n");
#endif
	return 1;
	}
	else greska("Sintaksna greska: Neocekivani token");
	return -1;
}

int f(){
	if(preduvid == LZ){
	int pom;
#ifdef ISPIS
	printf("f --> (e)\n");
#endif
	preduvid = yylex();
	pom= e();
	if(preduvid == DZ)
		preduvid = yylex();
	else greska("Sintaksna greska: Ocekivano je ).");
	return pom;
	}
	else if(preduvid == BROJ){
#ifdef ISPIS
	printf("f --> BROJ\n");
#endif
	preduvid = yylex();
	return yyval;
	}else greska("Sintaksna greska: Ocekivano je ).");
	return -1;
}

int main(){
	int rezultat;
	preduvid = yylex();
	
	rezultat = e();
	if(preduvid!=EOI)
		greska("Sintaksna greska: Visak karaktera na ulazu!");
	printf("Vrednost izraza je %d\n",rezultat);
	return 0;
}

