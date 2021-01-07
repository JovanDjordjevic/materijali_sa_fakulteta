# Skup je struktura podataka  bez ponavljanja elemenata

# s ce biti skup razlicitih karaktera reci abrakadabra
s = set("magija")
print( s )

b= ['magija', "pokus", 'abrakadabra', 'magija', "hokus" ]
# Stampamo skup ciji elementi su elementi liste b
print( set(b) )

# Ukoliko skup s sadrzi 'f' uklanjamo ga, ukoliko ne sadrzi dodajemo
# Za uklanjanje je neophodno da se proveri da li je element u skupu. 
# Ako uklanjamo 'f' pre provere da li je element skupa imacemo KeyError, 
# u slucaju da nije element skupa.
if 'f' not in s:
	s.add('f')
else: 
	s.remove('f')

# Definisemo skup od slova iz reci "mudro"	
c = set("mudro")

# Stampamo skupove pre primene operacija
print( "\n",s,"\n",c )

# Presek skupova
print( s&c )
print( s.intersection(c) )

# Unija skupova
print( s|c )
print( s.union(c) )

# Razlika skupova
print( s-c )
print( s.difference(c) )

# Simetricna razlika
print( s^c )
print( s.symmetric_difference(c))
	
