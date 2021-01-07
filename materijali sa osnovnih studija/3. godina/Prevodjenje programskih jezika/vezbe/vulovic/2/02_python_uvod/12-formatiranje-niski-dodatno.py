pitanja=['ime','zanimanje','mesto u kom zivim']
odgovori=['Pera','programer', 'Beograd']

print("\n\nI nacin\n")
for a,b in zip(pitanja,odgovori):
	print( 'Tvoje' + a + ' je: Moje' +a +' je '+b+'.' )

print("\n\nII nacin\n")
for a,b in zip(pitanja,odgovori):
	print( 'Tvoje {0} je: Moje {0} je {1:10}.'.format(a,b) )

print("\n\nIII nacin\n")	
# drugi nacin za formatiranje izlaza
for a,b in zip(pitanja,odgovori):
	print( 'Moje %s je: Moje %s je %10s.' %(a, a, b) )	
	
print("\n\nIV nacin\n")	
for a,b in zip(pitanja,odgovori):
	print( 'Moje %(pit)s je: Moje %(pit)s je %(odg)10s.' % {"pit":a, "odg":b} ) 	
	
print("\n\nV nacin\n")	
	# drugi nacin za formatiranje izlaza
for a,b in zip(pitanja,odgovori):
	print( 'Moje {pitanje} je: Moje {pitanje} je {odgovor:20s}.' .format(pitanje = a, odgovor = b) )	