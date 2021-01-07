# HTML datoteka cije se ime navodi kao prvi argument komandne linije
# skripta sadrzi tabelu u kojoj se nalaze rezultati odrzanog ispita. 
# Tabela ima tri kolone. U prvoj se nalazi ime i prezime studenta 
# u drugoj broj poena na teorijskom delu ispita i u trecoj broj poena
# na prakticnom delu ispita. 
# Napisati skript koji u datoteku "sortirano.txt" ispisuje studente 
# uredjene opadajuce po ukupnom broju poena.

import sys
import re

# Proveravamo da li je navedeno ime ulazne html datoteke
if len(sys.argv) == 1 or (re.fullmatch('.*\.html',sys.argv[1],re.I) is None):
  sys.exit('Prvi argument mora biti html datoteka!')

try:
  with open(sys.argv[1],"r") as ff:
    #procitamo celu datoteku u jednu nisku
    dat = ff.read()
except IOError:
  exit( "Neuspesno otvaranje i citanje datoteke: '%s'" % sys.argv[1])

i = 0;
studenti = []
#0 Savic Marko
#1 Pera Peric

poeni = []
# 0 120
# 1 190

ri = re.compile(r"<tr>" 
+r"\s*<td>\s*(?P<ime>[A-Za-z]+(?: +[A-Za-z]+)+)\s*</td>"
+r"\s*<td>\s*(?P<zadaci>0|[1-9]\d|100)\s*</td>"
+r"\s*<td>\s*(?P<teorija>0|[1-9]\d|100)\s*</td>"
+r"\s*</tr>")

m = ri.search(dat)

while m is not None:
  # pronasli smo studenta ubacujemo ga u listu
  studenti.append( m.group('ime'))
  ukupno = int(m.group('zadaci')) + int(m.group('teorija'))
  # print studenti[i], ukupno
  poeni.append(ukupno / 2.0)
  m=ri.search(dat,m.end())
  
# altrenativno, pretrazivanje  studenata je moglo i ovako
#for m in ri.finditer(dat):
  #studenti.append( m.group('ime'))
  #ukupno = int(m.group('zadaci')) + int(m.group('teorija'))
  #poeni.append(ukupno / 2.0)
  

sortirani_poeni = list(zip(poeni, studenti)  )

sortirani_poeni.sort(reverse=True)

#((23,1),(87,3) (87,9),(100,4))
#((100,4),(87,9),(87,3),(23,1))

try:
  with open('rezultati.txt','w') as f:
    for j,(bodovi,ime) in enumerate(sortirani_poeni):
      f.write(str(j+1) + ". " + ime + "\t\t" + str(bodovi) + "\n")
except IOError:
  sys.stderr.write("Neuspelo otvaranje file 'rezultati.txt'\n")
