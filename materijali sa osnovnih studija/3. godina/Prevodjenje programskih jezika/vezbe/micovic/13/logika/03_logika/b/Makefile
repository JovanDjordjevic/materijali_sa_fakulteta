GOAL = logic
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

$(GOAL): lex.yy.o parser.tab.o
	$(CXX) -o $@ $^

#the_set.o: the_set.cpp the_set.hpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.c: lexer.lex
	flex $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $<

.PHONY: clean

clean:
	rm *.o parser.tab.* parser.output lex.yy.* $(GOAL)

