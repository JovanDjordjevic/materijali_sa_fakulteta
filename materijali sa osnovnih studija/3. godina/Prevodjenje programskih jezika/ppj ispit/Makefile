izvrsni: lex.yy.c parser.tab.cpp skup.cpp 
	g++ -Wall -std=c++11 lex.yy.c parser.tab.cpp skup.cpp

lex.yy.c: lekser.l parser.tab.hpp skup.hpp
	flex lekser.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -v -d parser.ypp
