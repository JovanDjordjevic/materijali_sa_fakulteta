#!/usr/bin/python3

# Program racuna broj poena koje je student osvojio na ispitu na osnovu
# informacija u html fajlu.
# Svakom studentu je pridruzena jedna vrsta matrice u kojoj su tri kolone. Ime i prezime, 
# broj poena na zadacima i broj poena na teoriji. Konacan broj poena se dobija kao 
# srednja vrednost osvojenih poena na zadacima i osvojenih poena na teoriji. 
# Studente treba sortirati po broju osvojenih poena i to upisati u fajl rezultat.txt

import sys, re, os

# proveravam argumente komandne linije i proveravam da li drugi argument komandne linije
# ima ekstenziju .html
if len(sys.argv) < 2 or re.match(r'^.*\.html$', sys.argv[1]) is None:
	sys.exit("./poeni .html")

# ucitavam kompetan sadrzaj fajla
try:
	with open(sys.argv[1], "r") as f:
		podaci = f.read();
except IOError:
	sys.exit("File open failed")

# lista imena studenata
studenti = []
# lista poena koje su studenti osvojili (ukupno)
poeni = []

# regularni izraz koji opisuje red matrice koji je pridruzen svakom studentu
ri = re.compile(r"<tr>"+
r"\s*<td>\s*(?P<ime>[A-Za-z]+( [A-Za-z]+)+)\s*</td>"+
r"\s*<td>\s*(?P<zadaci>\d|[1-9]\d|100)</td>"+
r"\s*<td>\s*(?P<teorija>\d|[1-9]\d|100)</td>"+
r"\s*</tr>");

# trazim prvog studenta u fajlu
m = ri.search(podaci)

# ako sam nasao studenta
while m is not None:
	# dodam njegovo ime u listu studenti
	studenti.append(m.group('ime'))
	# izracunam osvojeni broj poena
	ukupno = int(m.group('zadaci')) + int(m.group('teorija'))
	# dodam poene u listu poeni
	poeni.append(ukupno/2);
	# i pokrenem pretragu ponovo
	m = ri.search(podaci, m.end())

# alternativno resenje, ali prirodnije i lepse
	
#for m in ri.finditer(podaci):
#	studenti.append(m.group(ime))
#	poeni.append((int(m.group('zadaci')) + int(m.group('teorija')))/2)

# po istom modelu kao prosli put sortirano studente
sortirani = sorted(zip(poeni, studenti))
sortirani.reverse()

# stampamo dobijeni rezultat
print(sortirani)
i = 1
# upisujemo rezultate u fajl
try:
	with open("rezultat.txt", "w") as f:
		for (p,s) in sortirani:
			f.write(str(i) + ". " + s + ", " + str(p) +"\n")
			i += 1
except IOError:
	sys.exit("File open failed")
