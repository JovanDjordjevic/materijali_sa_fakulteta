#!/usr/bin/python3

import sys

# funkcije u pajtonu se definisu na sledeci nacin
# def ime_funkcije(lista_argumenata):
#		blok_naredbi
#

# funkcija vraca niz fibonacijevih brojeva koji su manji od prosledjenog broja
# u slucaju da se ne prosledi broj, podrazumevana vrednost argumenta je 10
def fibonaci(n = 10):
	
	niz = []			# prazna lista u koju cemo upisivati fibonacijeve brojeve
	a,b = 0,1			# inicijalizujemo pocetne vrednsoti. a na 0, i b na 1
	# dok god ne dodjemo do broja veceg od n
	while (a < n):
		# nadovezujemo trenutni broj na listu
		niz.append(a)
		# i azuriramo vrednosti
		a,b = b, a+b
	
	# vrecamo kreirani niz kao povratnu vrednost funkcije
	# BITNO:
	# povratna vrednost funkcije moze da bude bilo koji tip podataka
	return niz

# definisemo funkciju main koja opisuje glavni program
def main():
	# ucitamo sa standardnog ulaza jedan int
	x = int(input("Unesite neki broj: "))
	
	# kreiramo niz fibonacijevih brojeva manjih od n
	niz = fibonaci(x)

	# stampamo dobijeni rezultat
	print(niz)
	# testiramo funkciju sa podrazumevanim argumentom
	print(fibonaci())	

# pozivamo funkciju main
# BTINO:
# izvrsavanje programa pocinje uvek od prve naredbe koja nije u okviru neke druge funkcije.
main()
