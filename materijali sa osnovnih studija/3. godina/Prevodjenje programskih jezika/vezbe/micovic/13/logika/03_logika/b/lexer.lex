%option noyywrap
%option nounput
%option noinput

%{
#include <iostream>
#include <string>

#include "parser.tab.hpp"
%}

%%
"/\\" {
    return and_tok;
}
"\\/" {
    return or_tok;
}
"<=>" {
    return eq_tok;
}
"=>" {
    return imp_tok;
}
"True" {
    return true_tok;
}
"False" {
    return false_tok;
}
":=" {
    return assign_tok;
}
[a-z][a-z0-9]* {
    return id_tok;
}
[!\n] {
    return *yytext;
}
[ \t] {}
. {
    std::cerr << "Leksicka greska: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
