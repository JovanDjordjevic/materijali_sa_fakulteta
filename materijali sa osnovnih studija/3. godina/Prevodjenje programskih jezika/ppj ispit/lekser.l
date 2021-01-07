%option noyywrap
%option noinput
%option nounput


%{
#include<iostream>
#include<cstdlib>
#include<string>
#include"skup.hpp"

using namespace std;

#include"parser.tab.hpp"
%}


%%
"\\/"     { return ILI; }
"/\\"     { return I; }
"\\"      { return RAZLIKA; }
print     { return PRINT; }
card      { return CARD; }
check     { return CHECK; }
".."      { return TT; }

-?(0|[1-9][0-9*]) { yylval.vr_broja=atoi(yytext);
                    return BROJ; }
[A-Za-z][A-Za-z0-9]* {  yylval.vr_id=new string(yytext); 
                        return ID; }

[={}\."',();:]   { return yytext[0]; }

[\n \t] { }
.       { cerr<<"Nepoznat karakter "<<yytext[0]<<endl;
          exit(EXIT_FAILURE);
        }

%%
