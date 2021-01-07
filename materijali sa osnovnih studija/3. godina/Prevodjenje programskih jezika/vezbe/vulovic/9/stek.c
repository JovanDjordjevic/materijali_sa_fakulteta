/*******************************
*  Gramatika je:
*  E -> E+T
*	|T
*  T -> T*F
*	|F
*  F => (E)
*	|num
*  Moramo se obavezno osloboditi leve rekurzije
*  pravila	skupovi izbora
*  E -> TE'	{ num , ( }
*  E'->	+TE'	{ + }
*	|eps	{ ) , EOI }
*  T -> FT'	{ ( , num }
*  T'-> *FT'	{ * }
*	|eps	{ + , ) , EOI }
*  F -> (E)	{ ( }
*	|num	{ num }
*  Skupove izbora smo dobili za sva pravila koja nisu epsilon
*  na osnovu skupova FIRST, a za epsilon pravila na osnovu
*  skupova FOLLOW
*******************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define EOI 0
#define PLUS 1
#define PUTA 2
#define LZ 3
#define DZ 4
#define BROJ  5

/* Metodu rekurzivnog spusta cemo sada implementirati simuliranjem rada potisnog automata,
koriscenjem steka.
Na stek cemo stavljati i terminale i neterminale.
Zbog toga navodimo i sledece predprocesorske direktive*/
#define E 6
#define EP 7
#define T 8
#define TP 9
#define F 10

#define _DEBUG 1

#define MAX 256
int preduvid;

void greska(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

/* Mozemo koristiti i leksicki analizator dobije alatom Flex.
 Ovde samo modifikujemo pocetni primer za rekurzivni spust, pa stoga zadrzavamo njegov leksicki analizator. */
int yylex()
{
	char ch = getchar();

	switch (ch) {
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

	if (isdigit(ch)) {
		while (isdigit(ch = getchar())) ;
		ungetc(ch, stdin);
		return BROJ;
	}

	greska("Leksicka greska!");
	return -1;
}

int stek[MAX];
int sp = 0;

int empty()
{
	if (sp == 0)
		return 1;
	else
		return 0;
}

int full()
{
	if (sp == MAX)
		return 1;
	else
		return 0;
}

int pop()
{
	if (empty()) {
		greska("Stek je prazan");
		return -1;
	} else
		return stek[--sp];
}

void push(int x)
{
	if (full())
		greska("Stek je pun");
	else
		stek[sp++] = x;
}

void print_stek()
{
	int i = sp - 1;
	for (; i >= 0; i--)
		printf("%d ", stek[i]);
	printf("\n");
}

int top()
{
	if (empty()) {
		greska("Stek je prazan");
		return -1;
	} else
		return stek[sp - 1];
}

int match(int x)
{
	return preduvid == x;
}

void advance()
{
	preduvid = yylex();
}

int main()
{
	advance();
	push(E);

	while (!empty()) {
		switch (top()) {
		case E:
			if (match(BROJ) || match(LZ)) {
#ifdef _DEBUG
				printf("E -->T EP\n");
				print_stek();
#endif
				pop();
				push(EP);
				push(T);
			} else
				greska
				    ("Sintaksna greska: Ocekivano je BROJ ili (");
			break;
		case EP:
			if (match(PLUS)) {
#ifdef _DEBUG
				printf("EP -->+ T EP\n");
				print_stek();
#endif
				pop();
				push(EP);
				push(T);
				push(PLUS);
			} else if (match(DZ) || match(EOI)) {
#ifdef _DEBUG
				printf("EP -->eps\n");
				print_stek();
#endif
				pop();
			} else
				greska
				    ("Sintaksna greska: Ocekivano je + ili ) ili EOI");
			break;
		case T:
			if (match(LZ) || match(BROJ)) {
#ifdef _DEBUG
				printf("T -->F TP\n");
				print_stek();
#endif
				pop();
				push(TP);
				push(F);
			} else
				greska("Sintaksna greska za T");
			break;
		case TP:
			if (match(PUTA)) {
#ifdef _DEBUG
				printf("TP --> * F TP\n");
				print_stek();
#endif
				pop();
				push(TP);
				push(F);
				push(PUTA);
			} else if (match(PLUS) || match(DZ) || match(EOI)) {
#ifdef _DEBUG
				printf("TP -->eps\n");
				print_stek();
#endif
				pop();
			} else {
				printf("reduvid je %d\n", preduvid);
				greska("Sintaksna greska za TP, preduvid je");
			}
			break;
		case F:
			if (match(LZ)) {
#ifdef _DEBUG
				printf("F --> ( E )\n");
				print_stek();
#endif
				pop();
				push(DZ);
				push(E);
				push(LZ);
			} else if (match(BROJ)) {
#ifdef _DEBUG
				printf("F --> broj\n");
				print_stek();
#endif
				pop();
				push(BROJ);
			} else
				greska("SIntaksna za F");
			break;
		default:
			if (match(top())) {
				pop();
				advance();
			} else
				greska("Sintaksna  za zavrsni simbol!");
		}		/* za switch */

	}			/* za while    */

	printf("Prepoznat je aritmeticki izraz!\n");
	return 0;
}
