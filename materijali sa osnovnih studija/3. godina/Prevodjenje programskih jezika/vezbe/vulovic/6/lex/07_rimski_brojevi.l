/* Program prepisuje datoteku na ekran,
  a sve sto moze da prepozna kao zapis rimskog broja prepisuje na ekran. */

%option noyywrap
%option nounput
%option noinput

%{
  int vrednost = 0;
  char zapis_broja[1000];
%}

hiljade M+
stotine C+|CD|DC*|CM
desetice X+|XL|LX*|XC
jedinice I+|IV|VI*|IX

%%
{hiljade} { vrednost += 1000*yyleng;
			strcat(zapis_broja, yytext);
 			}
{stotine} { if (strcmp(yytext, "CM") == 0)
              vrednost += 900;
            else if (strcmp(yytext, "CD") == 0)
              vrednost += 400;
            else 
              if( yytext[0] == 'D') { 
                vrednost += 500;
              if (yyleng <=4){  //DCCC
                vrednost += 100* (yyleng - 1);
              }
              else {
                fprintf(stderr, "\nNeispravan rimski broj %s\n",yytext);
                exit(EXIT_FAILURE);
              }
            }
            else
              if (yyleng <= 3){
                vrednost += 100* yyleng;
              }
              else {
                fprintf(stderr, "\nNeispravan rimski broj %s\n",yytext);
                exit(EXIT_FAILURE);
              }

			      strcat(zapis_broja, yytext);
        }
        
{desetice} { if (strcmp(yytext, "XC") == 0)
              vrednost += 90;
            else 
              if (strcmp(yytext, "XL") == 0)
                vrednost += 40;  
            else 
              if( yytext[0] == 'L') { 
                vrednost += 50;
              if (yyleng <= 4){  
                vrednost += 10* (yyleng - 1);
              }
              else { //LXXXXX
                fprintf(stderr, "\nNeispravan rimski broj %s\n",yytext);
                exit(EXIT_FAILURE);
              }
            }
            else
              if (yyleng <= 3){
                vrednost += 10* yyleng;
              }
               else {
                fprintf(stderr, "\nNeispravan rimski broj %s\n",yytext);
                exit(EXIT_FAILURE);
              }
			      strcat(zapis_broja, yytext);
          }

{jedinice} { if (strcmp(yytext, "IX") == 0)
              vrednost += 9;
            else if (strcmp(yytext, "IV") == 0)
              vrednost += 4;
            else if( yytext[0] == 'V') { 
              vrednost += 5;
              if (yyleng <= 4){  
                vrednost += (yyleng - 1);
              }
              else {  // VIIIII
                fprintf(stderr, "\nNeispravan rimski broj %s\n",yytext);
                exit(EXIT_FAILURE);
              }
            }
            else
              if (yyleng <= 3){
                vrednost +=  yyleng;
              }
               else {
                fprintf(stderr, "\nNeispravan rimski broj %s\n",yytext);
                exit(EXIT_FAILURE);
              }

			      strcat(zapis_broja, yytext);		
          }
       
[ \n\t.!?;"':]	{ if(vrednost > 0){
					          printf("%d", vrednost);
					          vrednost = 0;		
          					zapis_broja[0]='\0';
        					}					
        				  ECHO;
				        }											
.     {  if(vrednost > 0){
 	  		  vrednost = 0;
					printf("%s", zapis_broja);
					zapis_broja[0]='\0';
			  }
				
				ECHO; 
			}
%%

int main() {
  yylex();
  
  return 0;
}
