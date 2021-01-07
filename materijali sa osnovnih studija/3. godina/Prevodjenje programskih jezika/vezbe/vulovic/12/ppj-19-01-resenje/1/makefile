parser: lex.yy.o parser.tab.o
	g++ -Wall -Wextra -std=c++11 -o parser lex.yy.o parser.tab.o 

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -Wall -Wextra -std=c++11 -c -o parser.tab.o parser.tab.cpp 

lex.yy.o: lex.yy.c parser.tab.hpp
	g++ -Wall -Wextra -std=c++11 -c -o lex.yy.o lex.yy.c

lex.yy.c: lexer.lex parser.tab.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d parser.ypp
	
	
PHONY:  clean

clean: 
	rm -rf  *.o *.tab.* *.yy.* *.output* parser
