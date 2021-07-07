PROGRAM 	= linked_list.exe
CXX 		= cl
CXXFLAGS 	= /EHsc /std:c++17 /W4
LD 			= link
LDFLAGS 	= /DEBUG /out:$(PROGRAM)

$(PROGRAM) : main.obj list.obj
	$(LD)  $(LDFLAGS) main.obj list.obj 
	
list.obj: list.cpp list.hpp
	$(CXX) $(CXXFLAGS) /c list.cpp

main.obj: main.cpp
	$(CXX) $(CXXFLAGS) /c main.cpp

.PHONY: clean

clean:
	del *.obj *.pdb *.ilk *.exe
