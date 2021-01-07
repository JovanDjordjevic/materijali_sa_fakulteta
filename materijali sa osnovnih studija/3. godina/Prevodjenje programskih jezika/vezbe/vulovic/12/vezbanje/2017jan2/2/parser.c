/*
program : naredba TZ  pp     {PRINT VEKTOR ID}

pp : naredba TZ pp           {PRINT VEKTOR ID}
    | EOI                    {EOI }
            
naredba : PRINT izraz                  {PRINT} 
        | VEKTOR naredba               {VEKTOR} 
        | ID '=' izraz ',' naredba     {ID}    
        | ID ',' naredba               {ID}
        | ID '=' izraz                 {ID}
        | ID                           {ID}
        ;
        
izraz : ID                              
      |  '[' elementi ']' -         
      ;
      
elementi : elementi ',' BROJ            
        | BROJ                    
        ;
*/

#include<iostream>
#include<cstdlib>
#include<string>

#define YYDEBUG 1

using namespace std;

extern int yylex();

void yyerror(string s){
    cerr<<s<<endl;
    exit(EXIT_FAILURE);
}



int main(){
    yydebug=0;
    yyparse();

}
