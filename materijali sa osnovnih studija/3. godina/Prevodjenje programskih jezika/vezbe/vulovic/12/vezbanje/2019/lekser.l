%option noyywrap
%option noinput
%option nounput

%{
#include<iostream>
#include<cstdlib>

using namespace std;

#include"parser.tab.hpp"
%}


%%

print   {return PRINT;}
int     {return INT;}
list    {return LIST;}
"==" {return EQU;}
"<<"  {return SHL;}
">>"  {return SHR;}

0x(0|[1-9A-Fa-f][0-9a-fA-F]*) { sscanf(yytext,"%x",&yylval.vr_br);  return BROJ;}
0(0|[1-7][0-7]*) { sscanf(yytext,"%o",&yylval.vr_br); return BROJ;}
-?(0|[1-9][0-9]*) {yylval.vr_br=atoi(yytext); return BROJ;}

l[a-zA-Z0-9_]+ {yylval.li_id=new string(yytext); return LISTID;}
[_][a-zA-Z][a-zA-Z0-9]* { yylval.vr_id=new string(yytext); return ID; }

[=+\-*/&|^,();[\]~] {return yytext[0];}

[\n \t] {}
.       { cerr<<"nepoznat karakter "<<*yytext<<endl;
          exit(EXIT_FAILURE);
        }

%%
