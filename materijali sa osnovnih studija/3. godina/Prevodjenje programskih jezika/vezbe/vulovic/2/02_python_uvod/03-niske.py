# Definisemo promenljive tipa niska i stampamo ih na ekran
a = "Zdravo svima!\nDobro jutro!\n"

# Stampamo tip promenljive a
print( type(a) ) 
print( a )

b = "Pozdrav!"

print( b )

# Niske se mogu nadovezivati
print( a + b + "\n\n")

# i same sa sobom zadat broj puta
print( b * 3 )

# pri cemu se originalna niska nece promeniti.
print( b )

# Karakteri stringa se NE MOGU MENJATI!!!!!!!!!!!!!!!!.
# a[0] = 'z'

# Mogu se izdvojiti podniske koristeci indeksnu sintaksu
# Indeksi karaktera pocinju od 0 za  prvi i duzina-1 za poslednji karakter niske
# Dozvoljena je upotreba pozitivnih i negativnih celih brojeva za indeksiranje.
# Na primeru niske "Pozdrav!" :
#	 P	 o	 z	 d	 r	 a	 v	!
#	 0	 1	 2	 3	 4	 5	 6	7
#	-8	-7	-6	-5  	-4	-3	-2 	-1 

print( b[2:6] )   #dakle [)

# Stampa podnisku od pocetka niske do karaktera na indeksu 2, ali bez njega
print( b[:2] )

# Stampa nisku od karaktera na indeksu 4 do kraja niske b
print( b[4:] )

# Stampamo duzinu niske b
print( len(b) )

# Stampamo sve karaktere niske b
print( b[:] )

# Stampamo nisku od 3 karaktera do pretposlednjeg, neukljucujuci ga
print( b[2:-2] )

# Stampamo nisku od 2 karaktera do poslednjeg, neukljucujuci ga
print( b[1:len(b)-1] )

# Stampamo prvi karakter niske b 
print( b[-0] )

# Stampamo nisku koristeci samo negativne indekse
print( b[-5:-1] )

# Moramo biti oprezni kada koristimo konstrukciju b[i:j] da uvek vazi da je i<j
# i da i i j su validni indeksi karaktera niske.
# Inace, imacemo praznu nisku.
print( b[-3: 1] )
print( b[4:2] )
