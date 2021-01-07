/**********************************************************
***	       		   Zadatak 3                          		***
***	Cisti Pascal datoteku od komentara		              ***
***********************************************************/

%option noyywrap
%option nounput
%option noinput

%%

"{"[^}]*"}"		{
	/* Paskal komentari pocinju sa { a zavrsavaju se sa } 
	 * Kada prepoznamo neki paskal komentar, stavljamo praznu akciju
	 * tj. zelimo da se ne desi nista, a za sve ostalo za koje nismo
	 * definisali reg. izraz, na kraju liste reg. izraza se doda
	 * .    {ECHO;}
	 * Tako da sve ostalo ce ostati isto, osim onoga za sta smo specifikovali
	 * da se ne ispisuje
	 * Zagrade { i } imaju specijalno znacenje u lex datoteci, pa smo morali da
	 * ih navedemo pod navodnicima
	*/
	}
"(*"([^*]|"*"+[^*)])*\*+")"		{	
					/* Paskal komentari mogu da budu i u ovom obliku (* bla, bla, bla *)
					 * Kako su i zagrade ( i ), i * spec simboli i oni moraju da se navedu pod navodnicima
					 */
				}

%%

/* Treci deo datoteke se doslovno prenosi u lec.yy.c na sami kraj
 * U njemu cemo napisati main funkciju
 */

int main () {
	/* U kojoj samo pozivamo funkciju yylex() */
	yylex();

	return 0;
}
