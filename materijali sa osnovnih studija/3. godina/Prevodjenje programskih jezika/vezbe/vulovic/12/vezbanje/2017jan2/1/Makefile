izvrsni: lex.yy.c parser.tab.cpp vektor.cpp
	g++ -Wall -std=c++11 lex.yy.c parser.tab.cpp vektor.cpp
	
lex.yy.c: lekser.l
	flex lekser.l
	
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp
