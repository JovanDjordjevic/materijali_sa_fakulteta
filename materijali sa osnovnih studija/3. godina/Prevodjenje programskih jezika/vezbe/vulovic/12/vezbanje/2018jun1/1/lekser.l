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

[\n \t] {}
.       {cerr<<"nepoznata leksema "<<*yytext<<endl;
         exit(EXIT_FAILURE);
        }

%%
