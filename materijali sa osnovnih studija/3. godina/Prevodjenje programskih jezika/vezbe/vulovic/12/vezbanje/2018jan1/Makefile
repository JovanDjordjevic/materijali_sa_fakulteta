izvrsni: lex.yy.c parser.tab.cpp parser.tab.hpp MojVektor.cpp
	g++ -Wall -std=c++11 lex.yy.c parser.tab.cpp MojVektor.cpp

lex.yy.c: lekser.l parser.tab.hpp
	flex lekser.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp
