/**********************************************************
***			             Zadatak 1	                    		***
***	Broji linije i karaktere sa standardnog ulaza	      ***
***********************************************************/

/*  Ovo je obavezno da bi se pri nailasku na EOF zaustavilo 
 *  dalje citanje neke druge ulazne datoteke
 */
%option noyywrap

%{
	/* Ovaj deo koda se doslovno prenosi u lex.yy.c na sam pocetak.
	 * Ovde mozemo ukljucivati zaglavlja koja zelimo da koristimo, i/ili
	 * Globalne promenljive koje predstavljaju brojace.
	 */
	int num_lines = 0;
	int num_chars = 0;
%}

/* U ovom delu lex datoteke se stavljaju neke regularne definicije
 * koje nam koriste da uprostimo regularne izraze koje koristimo 
 * u drugom delu datoteke 
*/

/* Sledeci deo, drugi deo, je glavni deo datoteke, i u njemu se definisu 
 * regularni izrazi koje prepoznajemo zajedno sa akcijama koje zelimo da
 * se dese kad se pronadje tekst koji se uparuje sa regularnim izrazom sa leve strane akcije.
 * U njemu ne smemo da imamo C-ovske komentare na pocetku linije, dok u akcijama smemo.
 */
%%

\n {num_lines++; num_chars++;}
. {num_chars++;}

%%

/* Treci deo datoteke se doslovno prenosi u lex.yy.c na sami kraj
 * U njemu cemo napisati main funkciju
 */

int main () {
	/* U kojoj samo pozivamo funkciju yylex() */
	yylex();

	/* Ispisujemo izlaz */
	printf("Ukupan broj karaktera je %d, a broj redova je %d.\n", num_chars, num_lines);
return 0;
}
