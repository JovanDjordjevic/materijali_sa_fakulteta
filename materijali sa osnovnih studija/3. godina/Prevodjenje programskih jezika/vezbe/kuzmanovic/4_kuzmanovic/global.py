#!/usr/bin/python3

import sys

def f():
	# stampamo globalnu promnljivu s
	print(s)
	
def g():
	# proglasavamo da koristimo promenljivu s koja je globalna
	global s
	print(s)
	# menjamo vrednost globalnoj promenljivoj s
	# s obzirom da smo promenili globalnu promenljivu, ovo ce biti
	# vidljivo svim funkcijama koje koriste tu promenljivu
	s = "Hello world2"
	print(s)

def h():
	# lokalna promenljiva s
	# lokalne promenljive nastaju samim cinom dodele
	# onog momenta kada dodelimo vrednost promenljivoj, napravili smo lokalnu promenljivu
	s = "Zdravo svima!"
	print(s)
	
# promenljiva definisana van funkcije je globalna po definiciji
s = "Hello world\n"
print(s)

print("Poziv funkcije")
f()

print("Poziv g")
g()

print("Main")
print(s)

print("Poziv h")
g()
