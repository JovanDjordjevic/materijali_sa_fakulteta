/***********************************************************************
***			                     	Zadatak 4					                     ***
***	Program predstavlja prvi primer on-demand leksickog analizatora	 ***
***     Pronalazi celobrojne i razlomljene konstante u tekstu 			 ***
***	    I vraca razlicite tokene                                     ***
***********************************************************************/

%option noyywrap

%{
	/* Vrednost 0 je rezervisana za EOF i ne smemo je koristiti
	 * Ovo mozemo izvuci u neko zaglavlje koje bi ovde samo ukljucili
	 */
	#define F_CONST 1
	#define I_CONST 2
%}

/* Regularna definicija cifre */
DIGIT	[0-9]

%%

[+\-]?{DIGIT}+					{
							/* Celobrojne konstante */
							return I_CONST;
						}

[+\-]?{DIGIT}+\.{DIGIT}*([Ee][+\-]?{DIGIT}+)?	{
							/* Realne konstante */
							return F_CONST;
						}
.						{
							/* Prazna akcija da nam se nista ne bi ispisivalo */
						}
\n						{}


%%

/* Treci deo datoteke se doslovno prenosi u lec.yy.c na sami kraj
 * U njemu cemo napisati main funkciju
 */

int main () {
	/* Tokeni se predstavljaju celobrojnim konstantama */
	int token;
	/* Pozivamo funkciju sve dok ima tokena na ulazu 
	 * Kada leksicki analizator dodje do EOF, on ce vratiti token koji ima vrednost 0
	 */
	while ( (token = yylex())) {
		/* Prijavljujemo koji je token pronadjen
		 * i stampamo odgovarajucu leksemu
		 */
		switch(token) {
			case I_CONST:	printf("Pronadjena celobrojna konstanta: %s\n", yytext);
					break;
			case F_CONST:	printf("Pronadjena realna konstanta: %s\n", yytext);
					break;
		}
	}
	return 0;
}
