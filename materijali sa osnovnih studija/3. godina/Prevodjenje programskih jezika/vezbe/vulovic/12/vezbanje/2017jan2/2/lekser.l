%option noyywrap
%option noinput
%option nounput

%{
#include<iostream>
#include<cstdlib>
#include<string>
#include"parser.tab.hpp"

using namespace std;
%}


%%
vector {return VEKTOR;}
print {return PRINT;}
[a-z][0-9]* { return ID;}

-?(0|[1-9][0-9]*)(\.[0-9]+)? {return BROJ;}

[,;()\[\].:{}+=*-] {return *yytext;}
 
[\n \t] {}
.       {   cerr<<"nepoznata leksema "<<*yytext<<endl;
            exit(EXIT_FAILURE);
        }
%%
