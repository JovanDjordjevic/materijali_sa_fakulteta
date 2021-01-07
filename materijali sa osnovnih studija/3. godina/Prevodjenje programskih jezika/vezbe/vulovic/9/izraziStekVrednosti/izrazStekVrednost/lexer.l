%option noyywrap
%option nounput
%option noinput

%{
#include "tokeni.h"

extern int yylval;
%}

%%
[0-9]+  { yylval = atoi(yytext);	
	  return BROJ; }
"+"	return PLUS;
-	return MINUS;	
"*"	return PUTA;
"("	return OZ;
")"	return ZZ;
[ \t]	{}
\n	return EOI;
.	{
	  fprintf(stderr,"LEKSICKA greska: Neocekivan token (%s)\n",yytext);
	 exit(EXIT_FAILURE);
	 }
%%
/*
int main(){
  int token;
  
  while( (token =yylex()) != EOI)
    ;
  
  return 0;
}*/
