PROGRAM   = zad
CXX       = g++
CXXFLAGS  = -g -std=c++17 -Wall -Icatch/single_include

$(PROGRAM): test.o encoder.hpp
	cp test.cpp .`date +%Y%m%d-%H%M%S`test.cpp
	cp encoder.hpp .`date +%Y%m%d-%H%M%S`encoder.hpp
	$(CXX) -o $(PROGRAM) test.o

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


