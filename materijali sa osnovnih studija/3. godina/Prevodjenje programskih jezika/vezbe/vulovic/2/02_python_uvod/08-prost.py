# Ukljucujemo math biblioteku zbog funkcije za kvadratni koren
import math

# funkcija prost(n)  treba da proveri da li je broj n prost i da vrati:
# 1, ako je prost ;
# x, takvo da je x < n  i  n = x * (n/x), inace.

# Funkcija prost ima jedan argument sa podrazumevanom vrednosti 2.
# To omogucuje da se funkcija pozove i bez zadavanja argumenata. 
# U u tom slucaju n ce imati vrednost 2.
def prost(n = 2):
  if n == 2:
    return 1
  
  if n % 2 == 0:
    return 2
  
  # Gornja granica nam je donji ceo deo kvadratnog korena iz n, npr za n=49 je 7:
  # Neophodno je da konvertujemo u int zbog funkcije range
  for x in range(3, int(math.sqrt(n))+1, 2):
    if n % x == 0:
      return x
      break 
  # Ova else grana se odnosi na for petlju, i izvrsava se samo ako se 
	# iz petlje izaslo usled prestanka vazenja uslova ostanka u petlji
  else :
    return 1

try:
  # input() ispisuje poruku na ekran i preuzima liniju teksta sa ulaza.
  # int() taj tekst konvertuje u int, ukoliko imamo int u zapisu. Inace baca izuzetak.
  n = int(input('Unesite jedan ceo broj veci od 1: '))
  # ukoliko nije unet trazen broj bacamo izuzetak
  if n <= -1 :
    raise ValueError
except ValueError:
  exit('Potrebno je uneti prirodan broj veci od 1')

x = prost(n)
if( x == 1) :
  print( str(n) + " je prost" )
else:
  print( n, " = ", x, " * ", n//x )
    
