/**********************************************************
***			             Zadatak 2	                    		***
***	Proverava da li su zagrade ispravno uparene	        ***
***********************************************************/

%option noyywrap
%{
	/* Postavljamo broj otvorenih zagrada na 0 */
	int broj_otvorenih = 0;
%}

%%
"{"	{	ECHO; broj_otvorenih++;}
"}"	{
		/* ECHO je isto sto i printf("%s", yytext); */
		ECHO;
		/* Ne smemo zatvarati neotvorenu zagradu */
		if (broj_otvorenih==0) {
			fprintf(stderr, "Zagrade nisu korektno uparene!\n");
			/* Ovaj return se odnosi na fju yylex() */
			return(-1);
		}
		else broj_otvorenih--;
	}
  /* Sve ostale karaktere samo ispisujemo na izlaz. */
.	{ECHO;}
\n	{ECHO;}
%%

/* Treci deo datoteke se doslovno prenosi u lex.yy.c na sami kraj
 * U njemu cemo napisati main funkciju
 */

int main () {
	/* U kojoj samo pozivamo funkciju yylex() */
	/* Ako nam yylex() vrati -1 imamo nekorektno uparene zagrade i prekidamo program. */
	if (yylex() == -1)
		exit(EXIT_FAILURE);

	/* Ako je broj otvorenih zagrada jednak 0, onda su one korektno uparene */
	if (broj_otvorenih == 0)
		printf("Zagrade su korektno uparene.\n");
	else 
		printf("Nekorektno uparene zagrade!\n");

	return 0;
}
