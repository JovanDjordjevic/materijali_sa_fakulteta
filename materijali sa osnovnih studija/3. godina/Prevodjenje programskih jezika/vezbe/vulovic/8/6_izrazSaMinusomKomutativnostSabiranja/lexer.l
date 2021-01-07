%option noyywrap
%option noinput
%option nounput
%{
#include "token.h"

extern int yylval;
%}

%%
"-" return MINUS;
"+" return PLUS;
"*" return PUTA;
"(" return OZ;
")" return ZZ;
"/" return PODELJENO;

[0-9]+ {
      yylval = atoi(yytext);
      return BROJ;
      }
\n  return EOI;
.   {
    fprintf(stderr,
      "Leksicka greska. Nepoznata leksema \"%s\"\n",yytext);
    exit(EXIT_FAILURE);
  }
%%
/*
int main() {
  int token;
  
  while(token = yylex());
  
  return 0;
}*/