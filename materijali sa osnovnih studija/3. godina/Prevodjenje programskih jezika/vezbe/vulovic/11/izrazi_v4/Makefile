TARGET = izrazi_v4
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

$(TARGET): parser.tab.o lex.yy.o
	$(CXX) $(CXXFLAGS) -o $@ $^

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
lex.yy.c: lexer.lex parser.tab.hpp
	flex $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<

.PHONY: clean

clean:
	@rm $(TARGET) lex.yy.* *.tab.* *.output *~ 
	@echo 'Cleaned.'
	
	
