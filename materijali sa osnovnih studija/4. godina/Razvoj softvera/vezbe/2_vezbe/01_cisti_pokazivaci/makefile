# da bi se koristio lepo nmake, fajl se mora nazvati bas "makefile"
# a izgleda da kada se pravi fajl, ne smemo na windowsu da korisitimo ekstenziju .mk vec
# treba da ostane kao "File" tip (?)

# primmer makefile za windows
# makefileovi se prave u obliku:

# ono_sto_nastaje: od_cega_se_pravi, moze_imati_vise_fajlova
# [tab]	komanda_koja_treba_da_se_izvrsi

# npr:
# test.exe: main.obj
# 	link /DEBUG /out:test.exe

# main.obj: test.cpp
# 	cl /EHsc /std:c++17 /W4 /c test.cpp

# mozemo imati makroe, radi laksih izmena, oni se prave u obliku:
# IME_MAKROA = ime_onoga_sto_predstavlja
# i ti makroi se ispod koriste ovako: $(IME_MAKROA)

PROGRAM  = main.exe
CXX      = cl    					#c++ kompajler
CXXFLAGS = /EHsc /std:c++17 /W4     #opcije za kompajler, na windowsu se pisu ovako
LD       = link						#na windowsu je ovo linker
LDFLAGS  = /DEBUG /out:$(PROGRAM)   #komande koje prosledjujemo linkeru

$(PROGRAM): main.obj    #objektni fajlovi na linuxu su .o a na windowsu su .obj
	$(LD) $(LDFLAGS) main.obj

main.obj: main.cpp
	$(CXX) $(CXXFLAGS) /c main.cpp

# u makefileu mozemo zadati nesto kao funkcije
# npr funkciju "clean" koja brise nase objektne i exe i sotale nepotrebne fajlove pravimo ovako:
.PHONY: clean

clean:
	del *.obj *.pdb *.ilk *.exe