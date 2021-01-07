# Napisati Python skript koji ce preko argumenata komandne linije moci da primi
# naziv datoteke koju ce prepisati u drugu datoteku. Ako je naziv datoteke koja 
# se prepisuje npr. ulaz.txt prepisujemo njen sadrzaj u datoteku 
# sa nazivom kopija_ulaz.txt.

# Za pristup argumentima komandne linije iz skripta neophodno je da ukljucimo 
# zaglavlje sys
import sys

# Stampamo listu argumenata, koja nista drugo nego lista niski. 
# Prvi argument je uvek naziv skripta.
print( sys.argv, "\n")

# Ako imamo vise od 1 argumenta komandne linije, mozda imamo naziv datoteke
# koji bismo citali .Ukoliko nemamo prekidamo rad programa uz navedenu poruku
if len(sys.argv) == 1:
  exit('Nedovoljan broj argumenata komandne linije!\n')
  
  
# Imamo argument i pokusavamo da otvorimo datoteku za citanje.
# Neophodno je da proverimo da li je uspesno otvarena datoteka sa datim nazivom.
# Datoteka sa tim nazivom moze da ne postoji ili da nemamo pravo da je citamo. 
# U tom slucaju bi pokusaj citanja takve datoteke rezultovao izuzetkom IOError.
try: 
  # Otvaramo datoteku sa nazivom koji nam je prosledjen kao argument, 
  # sa namerom da je citamo.
  f = open(sys.argv[1], "r")
except IOError:
  exit("Neuspesno otvaranje datoteke " + sys.argv[1] )
  

# Datoteku koju smo uspesno otvorili mozemo uspesno citati na vise nacina
# - liniju po liniju 
#	 f.readline() vraca narednu liniju datoteke. Uzastopnim pozivanjem metoda 
#				procitacemo sve linije.
# 	 f.readlines() vraca listu svih linija iz datoteke

# - karakter po karakter ili u  blokovima od n karaktera ili u celosti
# 	 f.read() vraca nisku koja je celokupni sadrzaj datoteke 
# 	 f.read(n) vraca narednih n karaktera sadrzaja datoteke

# Citamo ceo sadrzaj
sadrzaj = f.read()

# Datoteka nije vise potrebna i zatvaramo je.
f.close()

# Otvaramo datoteku sa nazivom koji nam je prosledjen kao argument, sa namerom 
# da pisemo u nju. Ukoliko datoteka postoji prepisacemo njen stari sadrzaj, 
# ukoliko ne postoji kreiracemo je.
# Posto smo prethodnu datoteku vezanu za f zatvorili mozemo promenljivu f 
# ponovo da koristimo.
try:   
  f = open("kopija_"+sys.argv[1], "w")
except IOError:
  exit("Neuspesno otvaranje datoteke " + "kopija_" + sys.argv[1] )

# Upisujemo sadrzaj.
f.write(sadrzaj)

# Zatvaramo datoteku.
f.close()

