# Funkcija fibonacci(n)  treba da nam generise i vrati listu prvih elemenata 
# Fibonacijevog niza koji su manji od n.
# Na primer, za n =10 , vraca [1, 1, 2, 3, 5, 8]
def fibonacci(n = 6):
  niz = []
  a, b = 0, 1
  while a < n:
    niz.append(a)
    a, b = b, a + b

  return niz

print( fibonacci(2000))
# Funkcija se poziva sa podrazumevanom vrednosti argumenta i stampa se rezultat.
print( fibonacci() )
# Ispisujemo objekat tipa funkcija koji odgovara nasoj funkciji
print( fibonacci )