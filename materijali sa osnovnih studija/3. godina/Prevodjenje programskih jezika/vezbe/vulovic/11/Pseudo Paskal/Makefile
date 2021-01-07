program : lex.yy.c y.tab.c
	gcc -o program -Wall -ansi lex.yy.c y.tab.c

lex.yy.c: paskal.l
	flex paskal.l

y.tab.h y.tab.c: paskal.y
	yacc -d -v paskal.y