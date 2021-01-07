%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <string>
#include "polinom.hpp"
#include "parser.tab.hpp"

%}

%%
-?[0-9]+(\.[0-9]+)? {
    yylval.f_vrednost = atof(yytext);
    return BROJ;
}

[a-zA-Z][a-zA-Z0-9]+ {
    yylval.str_vrednost = new std::string(yytext);
    return ID;
}

[<>,\n+*()!$|'\[\]-] {
    return *yytext;
}

:=  {return DODELA;  /*Posebno i spojeno da bi morale zajedno da se prepoznaju, tj. bez ignorisanih belina izmedju*/}
!=  return NEQ;
==  return EQ;

[ \t] { }
. {
    std::cerr
        << "Leksicka greska: Neprepoznat karakter: "
        << *yytext
        << std::endl;
    exit(EXIT_FAILURE);
}
%%
