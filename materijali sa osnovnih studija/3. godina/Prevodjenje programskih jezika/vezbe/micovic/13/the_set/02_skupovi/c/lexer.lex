%option noyywrap
%option nounput
%option noinput
%{
#include <string>
#include <cstdlib>
#include "the_set.hpp"
#include "parser.tab.hpp"
%}

%%
print { return print_token; }
check { return check_token; }
[A-Za-z]+ {
    yylval.str_type = new std::string(yytext);
    return id_token;
}
([+-])?[0-9]+ {
    yylval.int_type = atoi(yytext);
    return num_token;
}
[\\={},:;}<] {
    return *yytext;
}
"/\\" {
    return intersect_token;
}
"\\/" {
    return union_token;
}
\.\. {
    return fromto_token;
}
[ \n\t] { }
. {
    std::cerr << "Lexical error. Unrecognized characted: " << *yytext << std::endl;
    exit(EXIT_FAILURE);
}
%%
