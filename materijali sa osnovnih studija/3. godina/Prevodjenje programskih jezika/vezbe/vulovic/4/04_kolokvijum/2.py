#  Napisati python-skript koji štampa na standardni izraz autora (−a), 
#  cenu (−c), izdavača (−i) ili godinu izdanja (−g) knjige koja se navodi kao
#  argument komande linije, u zavisnosti od prisutne opcije komandne linije 
#  (u slučaju da nema opcija, ispisati sve podatke o traženoj knjizi).
#  Informacije o knjigama se nalaze u fajlu knjige.xml koji ima sledeći format:

#  <?xml version="1.0" encoding="utf-8" ?>
#  <lista_knjiga>
#    <knjiga rbr="1" >
#      <naslov> Yacc </naslov>
#      <autor> Filip Maric </autor>
#      <godina_izdanja> 2004 </godina_izdanja>
#      <izdavac> Matematicki fakultet </izdavac>
#      <cena valuta="rsd"> 1000 </cena>
#    </knjiga>
#    <knjiga rbr="2" >
#      <autor> Fredrik Lundh </autor>
#      <cena valuta="eur"> 50 </cena>
#      <izdavac> O’Reilly & Associates </izdavac>
#      <godina_izdanja> 2001 </godina_izdanja>
#      <naslov> Python Standard Library </naslov>
#    </knjiga>
#  </lista_knjiga>

import re
import sys

autor = False
godina = False
izdavac = False
cena = False

naslov = None

if len(sys.argv) < 2:
	exit('Program se poziva sa %s -[acig] naslov_knjige' % sys.argv[0])

 
for a in sys.argv[1:]:
	if a[0] == '-':
		if a[1] == 'a':
			autor =True
		elif a[1] == 'c':
			cena = True
		elif a[1] == 'i':
			izdavac =True
		elif a[1] == 'g':
			godina = True
		else:
			exit('Nepodrzana opcija')
	else:# nije opcija 
		naslov = a
		
if naslov is None:
	exit('Jedan od argumenata mora biti naslov knjige')

try:
	with open("knjige.xml","r") as f:
		datoteka = f.read()
except IOError:
	exit('Neuspelo otvaranje datoteke knjige.xml')


ri = re.compile(r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[0-9]+)"\s*>\s*'
	+r"(?=.*?<naslov>\s*(?P<naslov>.*?)\s*</naslov>)"
	+r"(?=.*?<autor>\s*(?P<autor>[A-Z][a-z]+(?:\s+[A-Z][a-z]+)+)\s*</autor>)"
	+r'(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>rsd|eur)">\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
	+r"(?=.*?<izdavac>\s*(?P<izd>.*?)\s*</izdavac>)"
	+r"(?=.*?<godina_izdanja>\s*(?P<godina>[0-9]+)\s*</godina_izdanja>)"
	+r".*?</knjiga>", re.S)	

biblioteka = {}
#1 -> naslov, autor, godina, izdavac, cena, valuta
for m in ri.finditer(datoteka):
	biblioteka[m.group('rbr')] = [m.group('naslov'), m.group('autor'),m.group('godina'),m.group('izd'),m.group('cena'),m.group('valuta')]
	#print( biblioteka[m.group('rbr')])
	
for k,v in biblioteka.items():
	if v[0] == naslov:
		vrednosti = v[1:]
		break
else:
	exit('Nepostoji knjiga sa naslovom "%s"' %naslov)

if autor :
	print( vrednosti[0])
elif godina:
	print( vrednosti[1])
elif izdavac:
	print( vrednosti[2])
elif cena:
	print (vrednosti[3], vrednosti[4])
else:
	for v in vrednosti:
		print( v, end=" " )
	print ("\n")	
	
