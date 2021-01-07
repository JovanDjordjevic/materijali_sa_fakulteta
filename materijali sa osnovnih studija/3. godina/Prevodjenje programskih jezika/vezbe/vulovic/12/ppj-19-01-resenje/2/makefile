parser: lex.yy.c parser.cpp
	g++ -Wall -Wextra  -o parser lex.yy.c parser.cpp

lex.yy.c: lexer.lex parser.tab.hpp
	flex lexer.lex
	
PHONY:  clean

clean: 
	rm -rf   *.yy.*  parser
