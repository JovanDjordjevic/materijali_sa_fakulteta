%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>

/* Bison vodi racuna o tokenima i njihove definicije smesta u datoteku parser.tab.hpp
   Posto su nam potrebni za komunikaciju izmedju sintasnog i leksickog analizatora 
	ukljucujemo zaglavlje parser.tab.hpp u kom su tokeni definisani. */

#include "parser.tab.hpp"

using namespace std;
%}

%%
[0-9]+(\.[0-9]+)? { yylval.vrednost = atof(yytext);
		              return BROJ; }
[+*()/-] 		return *yytext;
[\n \t] 	{ /* beline ignorisemo */}
.			{	
				cerr << "Leksicka greska: Neprepoznat karakter " << *yytext << endl;
				exit(EXIT_FAILURE);}
%%
