PROGRAM = biginteger
CXX       = cl

$(PROGRAM): biginteger_test.o catch.o
	$(CXX) -o $(PROGRAM) $^
	
biginteger_test.o: test.cpp BigInteger.hpp
	$(CXX) -c $< -o $@
	
catch.o: catch.cpp
	$(CXX) -c $<

.PHONY: clean

clean:
	del *.o $(PROGRAM)

