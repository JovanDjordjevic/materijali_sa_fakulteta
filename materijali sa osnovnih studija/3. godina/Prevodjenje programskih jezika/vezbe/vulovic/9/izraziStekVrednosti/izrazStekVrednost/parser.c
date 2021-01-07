/*******************************
*  Gramatika je:
*  E -> E+T
*      |T
*  T -> T*F
*      |F
*  F => (E)
*      |num
*  Moramo se obavezno osloboditi leve rekurzije.
* 
*  pravilo        skup izbora
*  E -> TE'       { broj , ( }
*  E'-> +TE'      { + }
*       |eps      { ) , EOI }
*  T -> FT'       { ( , broj }
*  T'-> *FT'      { * }
*       |eps      { + , ) , EOI }
*  F -> (E)       { ( }
*       |num      { broj }
* 
* Uradicemo sintaksnu analizu odozgo nadole, simulacijom rada potisnog automata.
* 
* Za racunanje vrednosti, izraz se prevodi u postfiksnu notaicju, a potom se putem
* steka vrednosti racuna vrednost izraza. 
* Prevodjenje u postfiksnu notaciju se postize sledecom shemom.
* (u ovom slucaju se koristi leva asocijativnost) 
* 
*  E -> TE'			
*  E'-> +T {print(+)} E'		
*      |eps			
*  T -> FT'			
*  T'-> *F {print(*)} T'	
*      |eps			
*  F -> (E)		
*      |num {print(num.v)}	
* 
* Akcija u sredini pravila mozemo se osloboditi uvodjenjem pomocnih neterminala, 
* kao sto je opisano u sledecoj shemi.
* 
*  E -> TE'			
*  E'-> +T A1 E'		
*      |eps			
*  T -> FT'			
*  T'-> *F A2 T'		
*      |eps		
*  F -> (E)		
*      |num   { print(num.v) }
*  A1-> eps   { print(+) }
*  A2->eps    { print(*) }
* 
* Ukoliko zelimo i efektivno da se izracunava vrednost uvodi se pored steka za 
* parsiranje u stek vrednost i akcije menjaju.
* 
*  E -> TE'			
*  E'-> +T A1 E'		
*      |eps			
*  T -> FT'			
*  T'-> *F A2 T'		
*      |eps		
*  F -> (E)		
*      |num   { push(num.v) }
*  A1-> eps   { a=pop(); b=pop(); push(a+b) }
*  A2->eps    {a=pop(); b=pop(); push(a*b)  }
* 
* Oslanjanjem na stek vrednosti i uvedene pomocne neterminale
* mozemo uvesti i operatore - i / i uprkos tome sto koristimo 
* desno rekurzivnu gramatiku racunamo ispravne vrednosti izraza
* u kojima ucestvuju i ovi levo rekurzivni operatori. 
*******************************/


#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

#define MAX_DEPTH 256
//#define ISPIS 1
#define ISPIS_POST 2
extern int yylex();

void greska(char * s){
	fprintf(stderr,"%s",s);
	exit(EXIT_FAILURE);
}

int preduvid;
int yylval;

#define STACK(type, array) type array[MAX_DEPTH];\
		int sp_##array = 0;

#define empty(array) (sp_##array <= 0)
#define full(array) (sp_##array >= MAX_DEPTH)
#define top(array) (empty(array) ? greska("Top(): Prazan stek\n"),1 : (array[sp_##array-1]))		
#define pop(array) (empty(array) ? greska("Pop(): Prazan stek\n"),1 : (array[--sp_##array]))				
#define push(array, x) (full(array) ? greska("PUSH(): Pun stek\n"),1 : (array[sp_##array++] = (x)))		


int main(){
	STACK(int, parse_stack);
	STACK(int, value_stack);
	preduvid = yylex();
	
	push(parse_stack,E);
	
	while(!empty(parse_stack)){
		switch(top(parse_stack)){
			case E:
					if(preduvid == BROJ || preduvid == OZ){
						pop(parse_stack);
						push(parse_stack,EP);
						push(parse_stack,T);
#ifdef ISPIS		
						printf("E -> T EP\n");
#endif
					}
					else 
						greska("E: Ocekivano ...\n");
					break;
			case EP:
				if(preduvid == PLUS){
					pop(parse_stack);
					push(parse_stack,EP);
					push(parse_stack,A1);
					push(parse_stack,T);
					push(parse_stack,PLUS);
#ifdef ISPIS
					printf("EP -> + T A1 EP\n");
#endif
				}
				else
					if(preduvid == MINUS){
					pop(parse_stack);
					push(parse_stack,EP);
					push(parse_stack,A3);
					push(parse_stack,T);
					push(parse_stack,MINUS);
#ifdef ISPIS
					printf("EP -> - T A3 EP\n");
#endif
				}
				else if(preduvid == EOI || preduvid == ZZ){
					pop(parse_stack);
#ifdef ISPIS
					printf("EP -> eps\n");
#endif
				}
				else
					greska("EP: Ocekivano ...\n");
				break;
			case T:
				if(preduvid == BROJ || preduvid == OZ){
					pop(parse_stack);
					push(parse_stack,TP);
					push(parse_stack,F);
#ifdef ISPIS
					printf("T -> F TP\n");
#endif
				}
				else
					greska("T(): ocekuje ....\n");
				break;
			case TP:
				if(preduvid == PUTA){
					pop(parse_stack);
					push(parse_stack,TP);
					push(parse_stack, A2);
					push(parse_stack,F);
					push(parse_stack,PUTA);
#ifdef ISPIS
					printf("TP -> * F A2 TP\n");
#endif
				}
				else if(preduvid == PLUS || preduvid == MINUS || preduvid == ZZ || preduvid == EOI){
					pop(parse_stack);
#ifdef ISPIS
					printf("TP -> eps\n");
#endif
				}
				else greska("TP(): ocekuje ....\n");
				break;
			case F:
				if(preduvid == BROJ){
					pop(parse_stack);
					push(parse_stack,BROJ);
#ifdef ISPIS
					printf("F -> BROJ\n");
#endif
#ifdef ISPIS_POST
					printf("%d ",yylval);
#endif
					push(value_stack,yylval);
				}
				else if (preduvid == OZ){
					pop(parse_stack);
					push(parse_stack,ZZ);
					push(parse_stack,E);
					push(parse_stack,OZ);
#ifdef ISPIS
					printf("F -> ( E )\n");
#endif
				}
				else 
					greska("F: ocekuje broj ili (");
				break;
			case A1:{
				int a, b;
				pop(parse_stack);
#ifdef ISPIS
				printf("A1 -> eps");
#endif
#ifdef ISPIS_POST
				printf("+ ");
#endif
				b = pop(value_stack);
				a = pop(value_stack);
				push(value_stack,a+b);
				break;
			}
			case A2:{
				int a,b;
				pop(parse_stack);
#ifdef ISPIS
				printf("A2 -> eps");
#endif
#ifdef ISPIS_POST
				printf("* ");
#endif
				b = pop(value_stack);
				a = pop(value_stack);
				push(value_stack,a*b);
				break;
			}
			case A3:{
				int a,b;
				pop(parse_stack);
#ifdef ISPIS
				printf("A3 -> eps");
#endif
#ifdef ISPIS_POST
				printf("- ");
#endif
				b = pop(value_stack);
				a = pop(value_stack);
				push(value_stack,a-b);
				break;
			}
			default:
				if(top(parse_stack) == preduvid){
					pop(parse_stack);
					preduvid = yylex();
				}
				else switch(top(parse_stack)){
			case PUTA: greska("SIntaksna greska: ocekivano je *\n");
			case PLUS: greska("SIntaksna greska: ocekivano je +\n");
			case BROJ: greska("SIntaksna greska: ocekivano je BROJ\n");
			case OZ: greska("SIntaksna greska: ocekivano je (\n");
			case ZZ: greska("SIntaksna greska: ocekivano je )\n");		
				}
		}
	}
	
	if(preduvid != EOI){
		greska("Sintaksna greska: Previse tokena na ulazu\n");
	}
	
	printf("Vrednost izraza je  %d\n",top(value_stack));

	return 0;
}
