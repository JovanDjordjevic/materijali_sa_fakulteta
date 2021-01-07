#!/usr/bin/python3

import sys, re

# Program pronalazi sve linkove koji su poseceni u html fajlovima pocevsi
# od fajla koji korisnik prosledjuje kao argument komandne linije. Zatim, program
# racuna statistiku posecenosti i sortirano prikazuje posecenost svake stranice
# od najposecenije ka najmanje posecenoj.

# funkcija izracunava statistiku
def obradi_datoteke(dat):
	
	# ako sam vec obradio datoteku
	if (dat in obradjene_datoteke):
		# prekidam izvrsavanje funkcije
		return;
	
	# upisujem ima datoteke u listu obradjenih
	obradjene_datoteke.append(dat)
	
	# ucitavam ceo fajl u svoj program
	try:
		with open(dat, "r") as f:
			podaci = f.read()
	except IOError:
		sys.exit("File open failed: '" + dat +"'")
	
	# BITNO:
	# ukoliko treba da tumacim ceo fajl kao jednu liniju, potrebno je da ga celog ucitam
	# u memoriju programa. U ovom slucaju trazim linkove, a u html-u je potpuno validno da 
	# a tag moze da se prostire u vise redova. U skladu sa tim, bilo koji pokusaj da to opisem 
	# nekim regularnim izrazom ce biti promasen. 
	# Kao resenje ove situacije, namece se mogucnost da ucitam ceo fajl u memoriju i koristim
	# single line mode prilikom poklapanja regularnog izraza. Na taj nacin mogu da zanemarim apsolutno sve
	# prljavstine koje korisnik moze da smisli, jer ce za mene fajl uvek biti samo jedna linija
	
	
	# kompajliram regularni izraz koji opisuje linkove u html-u i ukljucujem ignore case i single line modove	
	ri = re.compile(r'<a\s+href\s*=\s*"([^"]+)">(.*?)</a>',re.I | re.S)
	
	# BITNO:
	# finditer metod vraca iterator nad svim poklapanjima u stringu koji mu je prosledjen kao argument
	
	# u petlji, iteriram kroz sva poklapanja
	for m in ri.finditer(podaci):
		url = m.group(1)		# izdvajam ime link ka stranici iz regex-a
		ime = m.group(2)		# izdvajam ime ime linka iz regex-a
		
		#if statistika.get(url) is not None: # ruzniji nacin, ali tacan
		
		# elegantniji nacin
		
		# proveravam da li je url u recniku
		if url in statistika:
			statistika[url] += 1	# ako jeste, uvecavam broj poseta
		else:
			statistika[url] = 1		# inace ga ubacujem u recnik i inicijalizujem broj sa 1
		# rekurzvino obradjujem procitani link
		obradi_datoteke(url)	
			
# proveravam argumente komandne linije			
if len(sys.argv) > 1:
	pocetna = sys.argv[1]
else:
	pocetna = "index.html"

# inicijalizujem globalnu listu 
obradjene_datoteke = []
# inicijalizujem recnik koji ce mi mapirati linkove za brojem pojava
# kljuc je link, vrednost je broj pojava
statistika = {}
# i obradjujem datoteke	
obradi_datoteke(pocetna)

# da bih sortirao linkove, prvo treba da napravim listu parova
# oblika (vrednost, kljuc) sto postizem sa funkcijom zip
#
# sorted uvek radi sortiranje po prvom argumentu u tupplovima i zato ovako pakujem listu
# sorted uvek radi sortiranje u rastuci poredak
popularnost = sorted(zip(statistika.values(), statistika.keys()))
# meni treba opadajuci, pa zato obrcem listu
popularnost.reverse()

# na kraju prikazujem sortirani sadrzaj 
print("")
for no, url in popularnost:
	print(url, no)
