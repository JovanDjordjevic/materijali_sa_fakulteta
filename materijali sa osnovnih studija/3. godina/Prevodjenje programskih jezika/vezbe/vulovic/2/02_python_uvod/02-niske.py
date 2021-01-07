print( 'Hello world!'  )

print( "Zdravo svima!\
Nekada je lakse zapisati\
 u vise redova tekst, \
a da on bude ipak \
tretiran kao \
jedna linija \
teksta!\n")

print( "Mozemo \t koristiti \n specijalne karaktere\v!")

print( "Jel' moguce imati i ' u sredini" +" ogradjene sa \" ?")

# Ako je niska ogradjena sa ', onda se " moze koristiti unutar te niske, 
# bez koriscenja \
print( 'levo,  a \t "ovo" je  desno' + " od reci 'levo'\n")


print( """Ukoliko je niska ogradjena sa
trostrukim navodnicima(ili apostrofima)
onda ce svaki 
prelazak u novi red biti prikazan.\n""")

# raw string
print( r"ovo\tse ispisuje\"doslovno.\n")
