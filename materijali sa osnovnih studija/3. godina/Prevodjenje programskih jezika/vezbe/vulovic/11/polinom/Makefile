polinom: lex.yy.c parser.tab.cpp polinom.cpp
	g++ -o polinom -Wall -std=c++11 lex.yy.c parser.tab.cpp polinom.cpp

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l
	
parser.tab.cpp parser.tab.hpp : parser.ypp
	bison -d -v parser.ypp
