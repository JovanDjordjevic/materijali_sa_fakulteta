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
[0-9]+		 {
            /* yylval je tipa union kako smo definisali u izrazi2.y 
				    isto tako atribut tokena BROJ je ceo broj polja vrednost unije yylval 
				    Nju treba inicijalizovati na konkretnu vrednost celog broja sa ulaza.
				    */ 
				    yylval.vrednost = atoi(yytext);
				    return BROJ; }
[+*()] 		return *yytext;
[\n \t] 	{ /* beline ignorisemo */}
.			{	
				cerr << "Leksicka greska: Neprepoznat karakter " << *yytext << endl;
				exit(EXIT_FAILURE);}
%%
