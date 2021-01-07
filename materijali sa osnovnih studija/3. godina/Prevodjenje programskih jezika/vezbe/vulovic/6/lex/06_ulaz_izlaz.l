/***************************************************************************
***			                  	Zadatak 5	                        			     ***
***	Nastavak prethodnog zadatka						                               ***
***	Program predstavlja prvi primer on-demand leksickog analizatora	     ***
***     Pronalazi celobrojne i razlomljene konstante u tekstu 			     ***
***	I vraca razlicite tokene						                                 ***
***	Ilustrujemo citanje i pisanje iz datoteka, umesto sa STDIN ili STDOUT***
*** 	Samo je main funkcija malo modifikovana	                    			 ***
****************************************************************************/

% option noyywrap % {
  /* Vrednost 0 je rezervisana za EOF i ne smemo je koristiti Ovo
     mozemo izvuci u neko zaglavlje koje bi ovde samo ukljucili */
#define F_CONST 1
#define I_CONST 2
%}

/* Regularna definicija cifre */
DIGIT[0 - 9]

    %%[+\-]? {
DIGIT}

+ {
  /* Celobrojne konstante */
  return I_CONST;
}

[+\-]? {
DIGIT}

+\. {
DIGIT}

*([Ee][+\-]? {
  DIGIT}

  +)? {
  /* Realne konstante */
  return F_CONST;
}

. {
  /* Prazna akcija da nam se nista ne bi ispisivalo */
}

\n {
}


%%
    /* Treci deo datoteke se doslovno prenosi u lec.yy.c na sami kraj
       U njemu cemo napisati main funkciju */
int main(int argc, char *argv[])
{

  /* Tokeni se predstavljaju celobrojnim konstantama */
  int token;

  /* Ako su zadati argumenti komandne linije iz kojih se cita ulaz,
     odnosno pise izlaz */
  if (argc > 1 && (yyin = fopen(argv[1], "r")) != NULL);
  else
    yyin = stdin;
  if (argc > 2 && (yyout = fopen(argv[2], "w")) != NULL);
  else
    yyout = stdout;

  /* Pozivamo funkciju sve dok ima tokena na ulazu Kada leksicki
     analizator dodje do EOF, on ce vratiti token koji ima vrednost 0 */
  while (token = yylex()) {
    /* Prijavljujemo koji je token pronadjen i stampamo odgovarajucu
       leksemu */
    switch (token) {
    case I_CONST:
      fprintf(yyout, "Pronadjena celobrojna konstanta: %s\n", yytext);
      break;
    case F_CONST:
      fprintf(yyout, "Pronadjena realna konstanta: %s\n", yytext);
      break;
    }
  }
  return 0;
}
