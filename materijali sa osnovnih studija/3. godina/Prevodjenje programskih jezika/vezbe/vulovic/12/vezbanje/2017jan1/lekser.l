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

date {return DATE;}

\'[]\'

[a-zA-Z][a-zA-Z0-9]* {return ID;}

[\n \t] {}
.       {cerr<<"nepoznata leksema "<<*yytext<<endl;
         exit(EXIT_FAILURE);
        }

%%
