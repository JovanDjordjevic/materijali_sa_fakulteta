# Dictionaries (dict)
dnevnik = {'Pera': 3,'Mira': 4, 'Dejan': 2}

print( dnevnik )
print (type(dnevnik))

# key() i values () su metode koje vracaju listu kljuceva, odnosno vrednosti 
# sacuvanih u mapi
print( dnevnik.keys() )
print(dnevnik.values() )
print("\n")

# Stampamo sortirane kljuceve 
print( sorted(dnevnik.keys()) )

# Peri menjamo ocenu na 5
# Ukoliko imamo Peru u dnevniku promenicemo mu ocenu,
# a da ne postoji unos za Peru ovom naredbom bismo ga dodali
dnevnik['Pera'] = 5
# Stampamo mapu
print( dnevnik, end="\n" )


# Metod get vraca vrednost u mapi za navedeni kljud ukoliko postoji
# vratice None ako nema unosa sa navedenim kljucem.
print( dnevnik.get('Sonja') ) 

print ("\n\n")

# Proverimo da li je Sonja u dnevniku
# Stampamo vrednost ako smo sigurni da postoji, inace imamo KeyError
if 'Sonja'  not in dnevnik.keys():
	dnevnik['Sonja']= 3
else:
	print( dnevnik['Sonja'] , "\n")	
  

# items() je metod koji nam vraca objekat koji ce nam sukcesivno generisati 
# parove kljuc vrednost iz mape
print( dnevnik.items())

# Proveravamo da li Pera ima 1
print( ("Pera",1) in dnevnik.items() )

print( "\n\n" )

# Ispis sadrzaja mape koriscenjem kljuca kao indeksa
for k in dnevnik.keys():
	print( k, dnevnik[k] )
	
print ("\n\n")	

# Ispis parova kljuc i odgovarajuca vrednost iz mape koriscenjem objekta 
#  dobijenog sa metodom items()
# k ce uvek uzimati vrednosti prvog elementa para, tj, kljuca, 
# v ce uzimati uvek vrednost drugog u paru, tj, vrednosti.
for k, v in dnevnik.items():
	print( k, '\t-> ', v )


