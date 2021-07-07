#primer nmake za vise cpp fajlova
PROGRAM 	= fraction.exe
CXX 		= cl
CXXFLAGS 	= /EHsc /std:c++17 /W4
LD 			= link
LDFLAGS 	= /DEBUG /out:$(PROGRAM)

$(PROGRAM) : main.obj Fraction.obj
	$(LD)  $(LDFLAGS) main.obj Fraction.obj 

Fraction.obj: Fraction.cpp Fraction.hpp
	$(CXX) $(CXXFLAGS) /c Fraction.cpp

main.obj: main.cpp
	$(CXX) $(CXXFLAGS) /c main.cpp

.PHONY: clean

clean:
	del *.obj *.pdb *.ilk *.exe
