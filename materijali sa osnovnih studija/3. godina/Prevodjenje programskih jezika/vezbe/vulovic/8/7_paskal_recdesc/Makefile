izvrsni: lex.yy.o paskal.o
	gcc -Wall -o izvrsni paskal.o lex.yy.o

paskal.o: paskal.c tokeni.h
	gcc -c -Wall paskal.c

lex.yy.o: lex.yy.c tokeni.h
	gcc -c -Wall lex.yy.c

lex.yy.c: paskal.l
	flex paskal.l
