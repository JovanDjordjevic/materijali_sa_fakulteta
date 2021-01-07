/*
e -> t ep                     { (, BROJ }     { e.v = ep.v , ep.nasledjen = t.v}
ep -> + t {print +} ep        { + }           { ep1.v = ep2.v , ep2.nasledjen = ep1.nasledjen + t.v }
    | - t {print - } ep       { - }           { ep1.v = ep2.v , ep2.nasledjen = ep1.nasledjen - t.v   
    | eps                     { ), EOI }      { ep1.v = ep1.nasledjen }
t -> f tp                     { BROJ, ( }     { t.v = tp.v }
tp -> * f {print *} tp        { * }           { tp1.v = tp2.v, tp2.nasledjen =  tp1.nasledjen  * f.v }
    | eps                     { +, -, ), EOI}    { tp1.v = tp1.nasledjen }
f -> BROJ { print BROJ.v }    { BROJ }        { f.v = BROJ.v}    
    | ( e )                   { ( }           { f.v = e.v }
    
 Nasledjen atribut se propagira od korena prema listovima stabla, a sintetizovani od listova prema korenu.   
 Nasledjene atribute prosledjujemo funkcijama preko argumenta,
 a sintetizovani funkcije vracaju preko povratnih vrednosti.
 
 Dakel kako se sintaksna analiza radi sa leva na desno tako se vrednost izraza racuna 
 i vrednost pocetnog dela izraza propagira se preko argumenta funkcijama kojima je potreban
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokeni.h"

// #define ISPIS 1

int preduvid;
int e();
int ep(int nasledjen );
int t();
int tp(int nasledjen);
int f();

int yylval;
extern int yylex();


int main() {
  preduvid = yylex();
  int vrednost = e();
  
  if( preduvid == EOI ){
    printf("\n\nRecenica odgovara jeziku zadatim gramatikom!\n");
  
    printf("\nVrednost izraza je %d\n", vrednost);
  }
  else
    printf("\nPrevise tokena na ulazu!\n");
  
  return 0;
}


int e() {
  if ( preduvid == OZ || preduvid == BROJ ){
#ifdef ISPIS    
      printf("e -> t ep\n");
#endif      
      int rezultat = t();
      return ep(rezultat);
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u e(): Ocekivano je (, broj, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int ep(int nasledjen) {
  if( preduvid == PLUS) {
#ifdef ISPIS
    printf("ep -> + t ep\n");
#endif
    preduvid = yylex(); 
    int rezultat = nasledjen + t();
    printf("+ ");
    return  ep(rezultat);
  }
  else if( preduvid == MINUS) {
#ifdef ISPIS
    printf("ep -> - t ep\n");
#endif
    preduvid = yylex(); 
    int rezultat = nasledjen - t();
    printf("- ");
    return  ep(rezultat);
  }
    
  else if( preduvid == ZZ || preduvid == EOI ){
#ifdef ISPIS
    printf("ep -> eps\n");
#endif
      return nasledjen;
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u ep(): Ocekivano je +,-,),EOI, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int t() {
  if(preduvid == BROJ || preduvid == OZ) {
#ifdef ISPIS
      printf("t -> f tp\n");
#endif   
      int rezultat = f();
      return  tp(rezultat);
  }
  else{
    fprintf(stderr, 
     "Sintaksna greska u t(): Ocekivano je (, broj, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int tp(int nasledjen) {
  if( preduvid == PUTA) {
#ifdef ISPIS    
    printf ("tp -> * f tp\n");
#endif    
    preduvid = yylex();
    int rezultat = nasledjen * f();
    printf("* ");
    return tp(rezultat);
  }
  else 
      if( preduvid == PODELJENO) {
#ifdef ISPIS    
    printf ("tp -> / f tp\n");
#endif    
    preduvid = yylex();
    int rezultat = nasledjen / f();
    printf("/ ");
    return tp(rezultat);
  }
  else 
    if( preduvid == PLUS || preduvid == MINUS ||  preduvid == ZZ || preduvid == EOI ){
#ifdef ISPIS      
      printf("tp -> eps\n");
#endif      
      return nasledjen;
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u tp(): Ocekivano je *,,/+, -,),EOI, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

int f() {
  if(preduvid == BROJ){
#ifdef ISPIS 
    printf("f -> BROJ\n");
#endif
    int rezultat = yylval;
    printf("%d ",yylval);
    preduvid = yylex();
    return rezultat;
  }
  else if(preduvid == OZ) {
#ifdef ISPIS
      printf("f -> ( e )\n");
#endif
      preduvid = yylex();
      int rezultat = e();
      if( preduvid == ZZ )
        preduvid = yylex();
      else {
        fprintf(stderr, 
     "Sintaksna greska u f(): Ocekivano je ), a pojavilo se %d\n", preduvid);
        exit(EXIT_FAILURE);
      }
      return rezultat;
  }
  else {
    fprintf(stderr, 
     "Sintaksna greska u f(): Ocekivano je (, BROJ, a pojavilo se %d\n", preduvid);
    exit(EXIT_FAILURE);
  }
}

// e=>t ep =>f tp ep => BROJ tp ep => BROJ ep => BROJ + t ep => BROJ + f tp ep =>
//   => BROJ + BROJ tp ep => BROJ + BROJ * f tp ep => BROJ + BROJ * BROJ tp ep
//   => BROJ + BROJ* BROJ
