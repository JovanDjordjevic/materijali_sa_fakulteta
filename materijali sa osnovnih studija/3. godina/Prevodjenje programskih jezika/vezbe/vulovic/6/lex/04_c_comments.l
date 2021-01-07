/******************************************************************
***			              Zadatak 7		                          		***
*** C program ocistiti od komentara i prebrojati redove fajla  	***
******************************************************************/

%option noyywrap

/*** Definisemo ekskluzino stanje comment, koje nam treba da bi specifikovali
 *** da se neke akcije desavaju samo ako smo trenutno u tom stanju
 *** Po defaultu, pocetno stanje je INITIAL, i sve do sada smo non-stop
 *** bili u tom stanju
 ***/
%x comment

%{
	/*** globalna promenljiva koja broji linije ***/
	int broj_linija = 0;
%}

%%
	/*** Kada se naidje na /*, prelazimo u stanje comment ***/
"/*"			{
				BEGIN(comment);
			}
<comment>[^*\n]*	{
				/*** U stanju comment gutamo sve osim novog reda i zvezdice, 
				 *** akcija nam je prazna, jer necemo ni da se ono sto
				 *** je u komentaru ispisuje na izlaz
				 ***/
			}
<comment>"*"*   	{
				/*** U komentarima gutamo zvezdice iza kojih nije / i \n ***/
			}
<comment>\n		{
				/*** Povecavamo broj linija ***/
				++broj_linija;
			}
<comment>\*+"/"               {
				/*** Kada naidjemo na kraj komentara, vracamo se u pocetno stanje ***/
				BEGIN(INITIAL);
			}		

			
\n			{
				/*** Ako naidjemo na nov red van komentara,
				 *** povecavamo broj redova, i stampamo nov red
				 ***/
				++broj_linija;
				ECHO;
			}
.                       {	/*** Ostale karaktere prepisujemo na izlaz,
                                      mozemo i da izostavimo i regularan izraz 
                                      i pridruzenu mu akciju ***/ }
%%

int main () {
	/*** pozivamo leksicki analizator ***/
	yylex();

	/*** Stampamo broj linija ***/
	printf("Broj linija je: %d\n", broj_linija);

	/*** Zavrsavamo uspesno program ***/
	return 0;
}

