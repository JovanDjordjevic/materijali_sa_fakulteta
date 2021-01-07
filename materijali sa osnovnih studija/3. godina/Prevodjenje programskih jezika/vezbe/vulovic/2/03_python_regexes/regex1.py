import re

poruka ="Odakle dolazi dobro je da je i stigao dovde!"
matcher= re.match(r'(?i)\w*', poruka)

if matcher is not None:
	print( poruka[matcher.start():matcher.end()])
#isto se postize i sa
	print( matcher.group())
else:
	print( 'Tekst sa pocetka niske ne odgovara regularnom izrazu')

m1 = re.search(r"\b(d([a-z]+))",poruka,re.S | re.I)   #ukljucujemo i DOTALL mode i IGNORECASE mode

if m1 is not None:
	print( m1.group() )
	print( poruka[m1.start():m1.end()] )
	print( m1.group(1,2) )
	print( m1.groups() )

reci = re.findall(r'\b(d([a-z]*)( ))',poruka)

print( "FINDALL: ", reci )

#stampamo nisku u kome je svaka podniska niske poruka uparena reg. izrazom zamenjena
print( re.sub(r"\b(d(?P<rec>[a-z]+))",r"\2-\1" ,poruka) )

str ="Hocemo li na basket?"
print( str.replace("basket","fudbal") )

#r"\b(?# ovo je komentar u reg izrazu )\w+"
