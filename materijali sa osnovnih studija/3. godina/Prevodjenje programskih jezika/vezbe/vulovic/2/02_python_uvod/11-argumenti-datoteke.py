# Napisati Python skript koji ce preko argumenata komandne linije moci da primi 
# naziv datoteke koju ce prepisati u drugu datoteku. Ako je naziv datoteke koja 
# se prepisuje, npr. ulaz.txt prepisujemo njen sadrzaj liniju po liniju 
# numerisane u datoteku linije_ulaz.txt

# Za pristup argumentima komandne linije iz skripta neophodno je da ukljucimo 
# zaglavlje sys
import sys

# Stampamo listu argumenata, koja nista drugo nego lista niski.
# Prvi argument je uvek naziv skripta.
print( sys.argv, "\n")

# Ako imamo vise od 1 argumenta komandne linije, mozda imamo naziv datoteke 
# koji bismo citali. Ukoliko nemamo prekidamo rad programa uz navedenu poruku.
if len(sys.argv) == 1:
  exit('Nedovoljan broj argumenata komandne linije!\n')
  
  
# Imamo argument i pokusavamo da otvorimo datoteku za citanje.
# Neophodno je da proverimo da li je uspesno otvarena datoteka sa datim nazivom.
# Datoteka sa tim nazivom moze da ne postoji ili da nemamo pravo da je citamo. 
# U tom slucaju bi pokusaj citanja takve datoteke rezultovao izuzetkom IOError.
try: 
  # Otvaramo datoteku sa nazivom koji nam je prosledjen kao argument, 
  # sa namerom da je citamo. Ako cemo mali broj operacija obaviti sa datotekom 
  # i zatvoriti, onda taj deo mozemo objediniti u with blok.
  
  # f je dostupno samo u bloku i odnosi se na otvorenu datoteku.
  # Prilikom napustanja with bloka datoteka ce biti automatski zatvorena 
  # i nije neophodno da je ekspicitno zatvorimo.
  with  open(sys.argv[1], "r") as f:  
    # citamo ceo sadrzaj po linijama
    sadrzaj = f.readlines()
except IOError:
  exit("Neuspesno otvaranje datoteke " + sys.argv[1] )
    

# Otvaramo datoteku sa nazivom koji nam je prosledjen kao argument, 
# sa namerom da pisemo u nju. Ukoliko datoteka postoji prepisacemo njen stari 
# sadrzaj, ukoliko ne postoji kreiracemo je. 
# Posto smo prethodnu datoteku vezanu za f zatvorili mozemo promenljivu f 
# ponovo da koristimo.
try:   
  f = open("linije_"+sys.argv[1], "w")
except IOError:
  exit("Neuspesno otvaranje datoteke " + "linije_" + sys.argv[1] )

# Upisujemo sadrzaj 
for i  in range( 0, len(sadrzaj)) : 
  # Ako zelimo da koristimo + za konkatenaciji niski onda ceo broj i moramo 
  # pretvoriti u njegovu reprezentaciju u vidu niske
  f.write( str(i) + ": " + sadrzaj[i])

# Zatvaramo datoteku
f.close()

