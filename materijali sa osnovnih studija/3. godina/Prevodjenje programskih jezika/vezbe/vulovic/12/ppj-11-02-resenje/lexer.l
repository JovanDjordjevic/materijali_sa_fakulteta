%option noyywrap
%{
  #include <string>
  #include "skup.hpp"
	#include "parser.tab.hpp"	
%}


%%
UniversalSet  return UNIVERSE;
check   return CHECK;
card    return CARD;
print   return PRINT;
[A-Z][A-Za-z0-9]*   { yylval.ime= new std::string(yytext);
			    return ID;}
[={,};:<~]  return *yytext;
".."	  return TT;
"\\/"   return U;
"/\\"   return P;
"\\"	  return R;

-?[0-9]+  { yylval.i_val = atoi(yytext);
	        return BROJ; }

[ \n\t] {}
. {
	  fprintf(stderr, "Nepoznata leksema: \"%s\"\n",yytext);
	  exit(1); }
%%
