/*
   Gramatika je:
   E -> E+T
      | T
   T -> T*F
      | F
   F -> (E)
      | BROJ
   Moramo se obavezno osloboditi leve rekurzije
   Ovde smo prepravili prethodni zadatak da pored toga sto
   preverava da li neki ulaz odgovara aritmetickom izrazu
   program i racuna vrednos tog izraza
   Svakom pravilu se dodaje odgovarajuca akcija,
   i na taj nacin dobijemo shemu prevodjenja
   pravila     skupovi izbora      akcije
   E -> TE'    { BROJ , ( }        {E.v = T.v + E'.v}
   E'-> +TE'   { + }               {E'1.v = T.v + E'2.v}
     |  eps    { ) , EOI }         {E'.v = 0}
   T -> FT'    { ( , BROJ }        {T.v = F.v * T'.v}
   T'-> *FT'   { * }               {T'1.v = F.v * T'2.v}
   |  eps      { + , ) , EOI }     {T'.v = 1}
   F -> (E)    { ( }               {F.v = E.v}
   |  BROJ   { BROJ }            {F.v = BROJ.v}
   Svim simbolima u stablu smo dodali atribute, tj. vrednosti
   Primetiti da smo ovde koristili desnu asovijativnost
   zbog desno rekurzivnih pravila, sto nam nije problem,
   jer imamo samo sabiranje i mnozenje.
   Da smo imali i oduzimanje ili deljenje, morali bi da obezbedimo
   levu asocijativnost iako imamo desno rekurzivna pravila
   To bi uradili tako sto bi svaki neterminal imao dva atributa
   */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BROJ 1
#define PLUS 2
#define PUTA 3
#define LZ 4
#define DZ 5
#define EOI 0

#define ISPIS 1
int preduvid;
int E();
int EP();
int T();
int TP();
int F();

void greska(const char* errmsg)
{
    fprintf(stderr,"%s\n",errmsg);
    exit(EXIT_FAILURE);
}

int yyval;

/*samostalno pisemo leksicki analizator*/
int yylex()
{
    char ch = getchar();
    switch(ch) {
        case '+':
            return PLUS;
        case '*':
            return PUTA;
        case '(':
            return LZ;
        case ')':
            return DZ;
        case '\n':
        case EOF:
            return EOI;
    }
    /* ako smo procitali cifru ?*/
    if (isdigit(ch)) {
        yyval = ch -'0';
        while(isdigit(ch=getchar()))
            yyval = yyval*10 +ch-'0';

        ungetc(ch, stdin);
        return BROJ;
    }

    greska("Leksicka greska: nepoznata leksema!");
    return -1;
}


int E() {
    if(preduvid == BROJ || preduvid == LZ) {
#ifdef ISPIS
        printf("E -> TE'\n");
#endif
        return T() + EP();
    } else
        greska("Sintaksna greska: Ocekivan je token BROJ ili (.");
    return -1;
}

int EP()
{
    if (preduvid== PLUS) {
#ifdef ISPIS
        printf("E' -> +TE'\n");
#endif
        preduvid = yylex();
        return T() + EP();
    }
    else if(preduvid == DZ || preduvid == EOI) {
#ifdef ISPIS
        printf("E' -> eps\n");
#endif
        return 0;
    } else
        greska("Sintaksna greska: Ocekivan je token + ili ) ili EOI");
    return -1;
}

int T()
{
    if (preduvid == LZ || preduvid == BROJ) {
#ifdef ISPIS
        printf("T -> FT'\n");
#endif
        return F() * TP();
    } else
        greska("Sintaksna greska: Ocekivano je LZ ili BROJ.");
    return -1;
}

int TP()
{
    if (preduvid == PUTA) {
#ifdef ISPIS
        printf("T' -> *FT'\n");
#endif
        preduvid = yylex();
        return F() * TP();
    } else if(preduvid == PLUS || preduvid == DZ || preduvid == EOI){
#ifdef ISPIS
        printf("TP -> eps\n");
#endif
        return 1;
    } else
        greska("Sintaksna greska: Neocekivani token");
    return -1;
}

int F()
{
    if (preduvid == LZ) {
        int pom;
#ifdef ISPIS
        printf("F -> (E)\n");
#endif
        preduvid = yylex();
        pom = E();
        if (preduvid == DZ)
            preduvid = yylex();
        else
            greska("Sintaksna greska: Ocekivano je ).");
        return pom;
    }
    else if (preduvid == BROJ) {
#ifdef ISPIS
        printf("F -> BROJ\n");
#endif
        preduvid = yylex();
        return yyval;
    } else
        greska("Sintaksna greska: Ocekivano je ).");
    return -1;
}

int main() {
    int rezultat;
    preduvid = yylex();

    rezultat = E();
    if (preduvid != EOI)
        greska("Sintaksna greska: Visak karaktera na ulazu!");
    printf("Vrednost izraza je %d\n",rezultat);
    return 0;
}

