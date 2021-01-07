PROGRAM = 07_rimski_brojevi.l

lexer: lex.yy.c
	gcc -o lexer -Wall lex.yy.c
	
lex.yy.c: $(PROGRAM)
	flex  $(PROGRAM)
