PROGRAM 	= student.exe
CXX 		= cl
CXXFLAGS 	= /EHsc /std:c++17 /W4
LD 			= link
LDFLAGS 	= /DEBUG /out:$(PROGRAM)

$(PROGRAM) : main.obj 
	$(LD)  $(LDFLAGS) main.obj 

main.obj: main.cpp
	$(CXX) $(CXXFLAGS) /c main.cpp

.PHONY: clean

clean:
	del *.obj *.pdb *.ilk *.exe
