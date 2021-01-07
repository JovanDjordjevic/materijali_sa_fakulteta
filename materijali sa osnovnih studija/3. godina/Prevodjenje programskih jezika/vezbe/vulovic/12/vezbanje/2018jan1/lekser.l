%option noyywrap
%option noinput
%option nounput

%{
#include<iostream>
#include<cstdlib>
#include<string>
#include"MojVektor.hpp"
#include"parser.tab.hpp"

using namespace std;

%}


%%
print {return PRINT;}
":="  {return DODELA;}

-?(0|[1-9][0-9]*)(\.[0-9]*)? {yylval.vr_br=atof(yytext); return BROJ;}

[a-z] {yylval.vr_id=yytext[0]; return ID;}

[<>.,;+*/\-|(){}\[\]] { return yytext[0];}
[\n \t] {}
.       {cerr<<"pogresna leksemma "<<*yytext<<endl;
        exit(EXIT_FAILURE);}

%%
