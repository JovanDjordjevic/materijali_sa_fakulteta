izvrsni: lex.yy.c parser.tab.cpp
	g++ -Wall -std=c++11 lex.yy.c parser.tab.cpp

lex.yy.c: lekser.l
	flex lekser.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d parser.ypp
