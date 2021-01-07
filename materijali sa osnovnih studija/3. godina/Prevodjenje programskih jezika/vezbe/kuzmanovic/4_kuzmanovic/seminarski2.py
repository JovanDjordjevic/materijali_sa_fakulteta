#!/usr/bin/python3

# Program lista sadrzaj direktorijuma koji se prosledjuje kao argument komandne linije
# Iz fajla indeksi koji se nalazi u tom direktorijumu cita informacije o indeksima i studentima.
# Na osnovu tog fajla, zadatak otvara direktorijume koji pripadaju studentima iz fajla indeksi
# i racuna statistiku


import sys, re, os

# polazni direktorijum
homedir = 'seminarski_radovi'

# recnik koji mapira indekse sa imenima studenata
studenti = {}

# kreiramo putanju do fajla indeksi
putanja = os.path.join(homedir, "indeksi")
try:
	# otvaramo fajl indeksi
	with open(putanja, "r") as f:
		# i citamo liniju po liniju
		for linija in f.readlines():
			# ako se linija zavrsava sa novim redom
			if (linija[-1] == '\n'):
				# brisemo novi red
				linija = linija[:-1]
			# ako linija ima sadrzaj oblika 'indeks, Ime i Prezime'
			if re.match(r'm[mnvlri]\d{5},\s*[A-Za-z ]+', linija) is not None:
				# razbijamo liniju oko zareza pracenog belinama, ili regularnim izrazom -> ',\s*'
				info = re.split(r',\s*', linija)
				# u recnik ubacujemo broj indeksa kao kljuc, a ime studenta kao vrednost
				studenti[info[0]] = info[1]
	# BITNO:
	# nakom sto se zavrsi with blok, automatski se zatvara fajl i nema potrebe da vodite racuna o tome
except IOError:
	# obrada gresaka
	sys.exit("File open failed")

# kompajliram regex koji opisuje pravilan naziv direktorijuma. U ovom slucaju radi se o alas nalogu
re_dir = re.compile(r'^m[mnvlri]\d{5}$');
# kompajliram regex koji opisuje pravilno ime fajla. U ovom slucaju radi se zadacima imenovanim brojevima 0-9,
# pri cemu je moguca ekstenzija ili java ili pas ili cpp ili c
re_file = re.compile(r'^(\d)\.(java|pas|c|cpp)$');

# max redni broj zadatka koji su studenti uradili
max_br_zad = 0
# recnik koji mapira studenta i broj zadatka sa ekstenzijom u kojoj je uradio zadatak
zadaci = {}

# listam polazni direktorijum
for f in os.listdir(homedir):
	stud_dir = os.path.join(homedir, f); # cim naidjem na neki fajl u direktorijumu, kreiram putanju do njega
	# BITNO: 
	# Uvek koristite os.path.join(...), nema potrebe da se dokazujete i pravite putanje rucno
	
	# ispitujem da li fajl ima odgovorajuce ime, tj. da li se radi o imenu koje je ejdnako alas nalogu
	m = re_dir.match(f)
	# ako je u pitanju direktorijum i ime je ispravno i student se nalazi u recniku studenti, tj. fajlu indeksi
	if os.path.isdir(stud_dir) and m is not None and f in studenti:
		# pamtim indeks studenta
		indeks = m.group();
		# i listam studentski direktorijum
		for sf in os.listdir(stud_dir):
			# pravim putanju do zadatka
			zadatak = os.path.join(stud_dir, sf);
			#  ispitujem da li fajl ima odgovorajuce ime, tj. da li se radi o broju zadatka pracenom ispravnom ekstenzijom
			m = re_file.match(sf);
			# ako je u pitanju regularni fajl ispravnog imena
			if (os.path.isfile(zadatak)) and m is not None:
				# izdvajam redni broj zadatka iz regex-a
				zad = int(m.group(1))
				# u recnik zapisujem tu informaciju
				# kljuc je uredjeni par (indeks, zadatak)
				# vrednost je ekstenzija u kojoj je uradjen zadata, tj. druga grupa u regex-u
				zadaci[(indeks, zad)] = m.group(2)
				# pamtim najveci broj zadatka
				if (zad > max_br_zad):
					max_br_zad = zad

# stampam dobijene rezultate
for indeks, ime in studenti.items():
	# prvo ime studenta
	print("\nIme:" + ime)
	# zatim iteriram kroz zadatke
	for i in range(1,max_br_zad):
		# i ako je student uradio zadatak, tj. nalazi se u recniku zadaci
		if (indeks, i) in zadaci:
			# stampam ekstenziju u kojoj je resen zadatak
			print("\t" + str(i) + ". " + zadaci[(indeks, i)])
		else:
			# inace stampam - kao znak da zadataka nije resen
			print("\t" + str(i) + ". -")
