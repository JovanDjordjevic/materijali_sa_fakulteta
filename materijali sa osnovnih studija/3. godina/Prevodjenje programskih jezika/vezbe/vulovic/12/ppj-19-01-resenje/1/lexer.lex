%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "parser.tab.hpp"
%}

%%

print { return PRINT; }

int { return INT; }

list { return LIST; }

"<<" { return SHL; }

">>" { return SHR; }

"==" { return EQV; }

[_][a-zA-Z][a-zA-Z0-9]* { yylval.ime = new std::string(yytext);
                          return ID; }

(0|[1-9][0-9]*) {
           yylval.broj = atoi(yytext);
		       
		       return BROJ;
		     }

0x(0|[1-9A-F][0-9A-F]*) {
             sscanf( yytext, "%x",&yylval.broj);
             return BROJ;
        }

0(0|[1-7][0-7]*) {
           sscanf( yytext, "%o",&yylval.broj);
           return BROJ;
        }
l[a-zA-Z0-9_]+ { yylval.ime = new std::string(yytext);
                          return LID;}
        
[=+\-*/&|^,();[\]~] { return *yytext; }

[ \t\n] { }

. { std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE); }

%%
