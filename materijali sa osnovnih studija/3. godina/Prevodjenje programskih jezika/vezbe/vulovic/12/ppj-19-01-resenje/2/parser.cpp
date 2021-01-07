/*

program -> naredba nizp {IME, PRINT}
	   | eps {EOI}

nizp -> TZ naredba nizp {TZ}
	| eps {EOI, TZ}

naredba -> IME DOD izraz {IME}
	| PRINT OZ IME ZZ {PRINT}

izraz -> term izrp {BROJ, IME}

izrp -> AND term izrp {AND}
      | OR term izrp {OR}
      | term {BROJ, IME}
      | NOT term {NOT}

term -> BROJ
      | IME
*/

#include <iostream>
#include <cstdlib>
#include "tokeni.hpp"

extern int yylex();
int preduvid;

void nizp();
void naredba(){/*...*/};
void izraz();
void izrp();
void term();

void program()
{
  if (preduvid == IME || preduvid == PRINT)
      naredba();
  else if (preduvid == EOI)
      {/*...*/}
  else {/*yyerror("program");*/}
}

int main()
{
  preduvid = yylex();
  
  program();
  
  exit(EXIT_SUCCESS);
}
