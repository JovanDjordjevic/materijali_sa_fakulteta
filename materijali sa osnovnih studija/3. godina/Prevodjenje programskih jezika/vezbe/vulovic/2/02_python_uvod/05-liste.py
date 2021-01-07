# Iteriranje kroz liste i stringove
# Naredbe grananja i petlje

a="Moze i 0vako."
b=""

# Na osnovu niske a formiramo nisku b tako sto:
# samoglasnike zamenjujemo velikim samoglasnikom
# karakter koji nije slovo zamenjujemo sa -, a sve ostale prepisujemo 
for x in a:
  if x.isupper() or x.lower() in ('a','e', 'i', 'o', 'u'):
    b = b + x.upper()
  elif not x.isalpha() :
    b = b +  '-'
  else :
    b += x  
print( a )
print( b )

print()

# Zelimo da napisemo sve stepene broja 2 od 0. to 10.
# range(start, stop, step) 
# Funkcija kreira objekat koji generise sekvencu celih brojeva 
# pocevsi od celog broja start do broja stop sa celobrojnim korakom step
# range(0, 11, 1) je potrebno za ovaj zadatak
# Ako je start 0, moze se izostaviti jer je to njegova podrazumevana vrednost. 
# Takodje, ukoliko je step 1, moze se izostaviti.
# range(0, 11,1)  <=> range(11)
for i in range(0, 11, 1):
  print( 2, "^", i, "=", 2**i, end = "\n" )
print()

print()
  
# Stampanje svakog elementa liste u novom redu.
l = ['ovde', 'tamo', 'negde', 'svuda']
for x in l:
  print( x  )

print()

# Ukoliko u iteracijam planiramo da menjamo listu, posebno, da uticemo na njenu 
# duzinu, bolje je ne iterirati kroz originalnu listu vec kroz kopiju.
for x in l[:] :
  l.insert(0,x)
# Ukloniti [:] iza l u uslovu ostanka u petlji i naci cemo se u beskonacnoj 
# petlji jer svakom iteracijom produzavamo listu za jedan element.  

print()  

# Stampamo elemente liste razdvojene zarezima, koristeci indeksnu sintaksu  
for i in range(len(l)):
  if i != len(l) - 1:
    print( l[i], end= ", ") 
  else:
    print( l[i], end= "\n\n")   

# II nacin
i = 0
while i < len(l):
  if i != len(l) - 1:
    print( l[i], end= ", ") 
  else:
    print( l[i], end= "\n\n")
  i += 1	
  
# Nacin za kreiranje liste 
l = [ a for a in range(10) ]
print( l )
