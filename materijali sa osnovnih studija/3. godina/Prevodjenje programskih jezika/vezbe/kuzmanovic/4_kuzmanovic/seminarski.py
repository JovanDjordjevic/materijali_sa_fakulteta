#!/usr/bin/python3

# Program lista sadrzaj direktorijuma koji se prosledjuje kao argument komandne linije

# BITNO:
# ukoliko vam u programu treba bilo koja usluga operativnog sistema, morate da ukljucite modul os
import sys, re, os

# proveravam argumente komandne linije
if len(sys.argv) > 1:
	homedir = sys.argv[1]
else:
	homedir = '.'

# kompajliram regex koji opisuje pravilan naziv direktorijuma. U ovom slucaju radi se o alas nalogu
re_dir = re.compile(r'^m[mnvlri]\d{5}$')
# kompajliram regex koji opisuje pravilno ime fajla. U ovom slucaju radi se zadacima imenovanim brojevima 0-9,
# pri cemu je moguca ekstenzija ili java ili pas ili cpp ili c
re_file = re.compile(r'^(\d)\.(pas|java|cpp|c)$')

# listam polazni direktorijum
for f in os.listdir(homedir):
	dirPath = os.path.join(homedir, f);	# cim naidjem na neki fajl u direktorijumu, kreiram putanju do njega
	# BITNO: 
	# Uvek koristite os.path.join(...), nema potrebe da se dokazujete i pravite putanje rucno
	
	# ispitujem da li fajl ima odgovorajuce ime, tj. da li se radi o imenu koje je ejdnako alas nalogu
	m = re_dir.match(f)
	# ako je u pitanju direktorijum i ime je ispravno
	if os.path.isdir(dirPath) and m is not None:	
		# stampam naziv direktorijuma na koji sam naisao
		print("\n" + m.group())
		# i listam redom direktorijum
		for sf in os.listdir(dirPath):
			# kreiram putanju do fajla u studentskom direktorijumu
			path = os.path.join(dirPath, sf)
			#  ispitujem da li fajl ima odgovorajuce ime, tj. da li se radi o broju zadatka pracenom ispravnom ekstenzijom
			m = re_file.match(sf)
			# ako je u pitanju regularni fajl ispravnog imena
			if os.path.isfile(path) and m is not None:
				# stampam naziv fajla
				print("\t" + m.group())
				
			
