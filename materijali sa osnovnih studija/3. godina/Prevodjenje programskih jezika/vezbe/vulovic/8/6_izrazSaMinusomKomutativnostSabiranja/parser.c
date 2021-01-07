/*
E -> T EP                     { (, broj }     { E.v = T.v + EP.v }
EP -> + T {print +} EP        { + }           { EP1.v = T.v + EP2.v }
    | - T {print - } EP       { - }           { EP1.v =  EP2.v - T.v }
    | eps                     { ), EOI }      { EP1.v = 0 }
T -> F TP                     { broj, ( }     { T.v = F.v * TP.v }
TP -> * F {print *} TP        { * }           { TP1.v = F.v * TP2.v }
    | eps                     { +, -, ), EOI}    { TP1.v = 1 }
F -> broj { print broj.v }    { broj }        { F.v = broj.v}
    | ( E )                   { ( }           { F.v = E.v }
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

// #define ISPIS 1

int preduvid;
int E();
int EP();
int T();
int TP();
int F();

int yylval;
extern int yylex();


int main() {
  preduvid = yylex();
  int vrednost = E();
  
  if( preduvid == EOI ){
    printf("\n\nRecenica odgovara jeziku zadatim gramatikom!\n");
  
    printf("\nVrednost izraza je %d\n", vrednost);
  }
  else
    printf("\nPrevise tokena na ulazu!\n");
  
  return 0;
}


int E() {
  if ( preduvid == OZ || preduvid == BROJ ){
#ifdef ISPIS    
      printf("E -> T EP\n");
#endif      
      return  T() + EP();
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u E(): Ocekivano je (, broj, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int EP() {
  if( preduvid == PLUS) {
#ifdef ISPIS
    printf("EP -> + T EP\n");
#endif
    preduvid = yylex(); 
    int rezultat = T();
    printf("+ ");
    return  rezultat + EP();
  }
  else if( preduvid == MINUS) {
#ifdef ISPIS
    printf("EP -> - T EP\n");
#endif
    preduvid = yylex(); 
    int rezultat = T();
    printf("- ");
    return  EP() - rezultat;
  }
    
  else if( preduvid == ZZ || preduvid == EOI ){
#ifdef ISPIS
    printf("EP -> eps\n");
#endif
      return 0;
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u EP(): Ocekivano je +,-,),EOI, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int T() {
  if(preduvid == BROJ || preduvid == OZ) {
#ifdef ISPIS
      printf("T -> F TP\n");
#endif      
      return F() * TP();
  }
  else{
    fprintf(stderr, 
     "Sintaksna greska u T(): Ocekivano je (, broj, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int TP() {
  if( preduvid == PUTA) {
#ifdef ISPIS    
    printf ("TP -> * F TP\n");
#endif    
    preduvid = yylex();
    int rezultat = F();
    printf("* ");
    return rezultat * TP();
  }
  else 
      if( preduvid == PODELJENO) {
#ifdef ISPIS    
    printf ("TP -> / F TP\n");
#endif    
    preduvid = yylex();
    int rezultat = F();
    printf("/ ");
    return TP()/rezultat;
  }
  else 
    if( preduvid == PLUS || preduvid == MINUS ||  preduvid == ZZ || preduvid == EOI ){
#ifdef ISPIS      
      printf("TP -> eps\n");
#endif      
      return 1;
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u TP(): Ocekivano je *,/,+, -,),EOI, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int F() {
  if(preduvid == BROJ){
#ifdef ISPIS 
    printf("F -> BROJ\n");
#endif
    int rezultat = yylval;
    printf("%d ",yylval);
    preduvid = yylex();
    return rezultat;
  }
  else if(preduvid == OZ) {
#ifdef ISPIS
      printf("F -> ( E )\n");
#endif
      preduvid = yylex();
      int rezultat = E();
      if( preduvid == ZZ )
        preduvid = yylex();
      else {
        fprintf(stderr, 
     "Sintaksna greska u F(): Ocekivano je ), a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
      }
      return rezultat;
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u F(): Ocekivano je (, BROJ, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

// E=>T EP =>F TP EP => broj TP EP => broj EP => broj + T EP => broj + F TP EP =>
//   => broj + broj TP EP => broj + broj * F TP EP => broj + broj * broj TP EP
//   => broj + broj* broj
