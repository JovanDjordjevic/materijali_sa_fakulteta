#!/usr/bin/python3

import sys

# funkcija ispituje da li je prosledjeni broj prost
def prost(n):
	
	if (n == 2):
		return 1
	
	if (n%2 == 0):
		return 2
		
	for i in range(3, n//2, 2):
		if (n % i == 0):
			return i
			
	return 1

# obrada gresaka u pajtonu se postize pravilnom upotrebom izuzetaka
try:
	# ucitavamo broj sa standaradnog ulaza
	x = int(input("Unesite broj"));
	# u slucaju da broj nije odgovarajuci
	if (x <= 1):
		# dizemo izuzetak
		raise ValueError
except ValueError:
	# ako smo uhvatili izuzetak, desila se greska. Ili korisnik nije uneo broj pa je puklo kastovanje
	# ili je broj koji je uneo neodgovarajuci
	sys.exit("Broj mora da bude veci od 1")
	
# ispitujemo sam broj
rezultat = prost(x)
# i u zavisnosti od rezultat prikazujemo korisniku poruku
if (rezultat == 1):
	print("Broj je prost")
else :
	#print("Broj nije prost")
	print("%d = %d * %d"%(x, rezultat, x//rezultat))
	
	
