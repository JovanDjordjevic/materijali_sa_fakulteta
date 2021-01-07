#!/usr/bin/python3

# Program pronalazi sve linkove koji su poseceni u html fajlovima pocevsi
# od fajla koji korisnik prosledjuje kao argument komandne linije

import sys, re

# funkcija obradjuje fajlove i upisuje imena datoteka koje je obradila u 
# listu obradjene_datoteke
def obradi_datoteke(dat):
	
	# cim pozovem funkciju, odmah pamtim putanju da bih na taj nacin
	# izbegao beskonacnu rekurziju
	# BITNO:
	# obradjene_datoteke je globalna lista i ovo je potpuno validno i vidljivo svima nakon zavrseteka funkcije
	obradjene_datoteke.append(dat)
	
	# ucitavam ceo fajl u svoj program
	try:
		with open(dat, "r") as f:
			podaci = f.read()
	except IOError:
		sys.exit("File open failed")
	
	# BITNO:
	# ukoliko treba da tumacim ceo fajl kao jednu liniju, potrebno je da ga celog ucitam
	# u memoriju programa. U ovom slucaju trazim linkove, a u html-u je potpuno validno da 
	# a tag moze da se prostire u vise redova. U skladu sa tim, bilo koji pokusaj da to opisem 
	# nekim regularnim izrazom ce biti promasen. 
	# Kao resenje ove situacije, namece se mogucnost da ucitam ceo fajl u memoriju i koristim
	# single line mode prilikom poklapanja regularnog izraza. Na taj nacin mogu da zanemarim apsolutno sve
	# prljavstine koje korisnik moze da smisli, jer ce za mene fajl uvek biti samo jedna linija
	
	
	# kompajliram regularni izraz koji opisuje linkove u html-u i ukljucujem ignore case i single line modove
	ri = re.compile(r'<a\s+href\s*=\s*"(.*?)">.*?</a>', re.I | re.S);
	
	# BITNO:
	# finditer metod vraca iterator nad svim poklapanjima u stringu koji mu je prosledjen kao argument
	
	# u petlji, iteriram kroz sva poklapanja
	for m in ri.finditer(podaci):
		# citam link na koji pokazuje a tag
		url = m.group(1)
		# i ako se taj link ne nalazi u listi vec obradjenih datoteka
		if url not in obradjene_datoteke:
			# rekurzivno je obradjujem
			obradi_datoteke(url)	

# proveravam argumente komandne linije
if len(sys.argv) > 1:
	pocetna = sys.argv[1]
else:
	pocetna = "index.html"

# inicijalizujem globalnu listu i obradjujem datoteke
obradjene_datoteke = []
obradi_datoteke(pocetna)

# na kraju samo stampam sadrzaj liste
for d in obradjene_datoteke:
	print(d)
