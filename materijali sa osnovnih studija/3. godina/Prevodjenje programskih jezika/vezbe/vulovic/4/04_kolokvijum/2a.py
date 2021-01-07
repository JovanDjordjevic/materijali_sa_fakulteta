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

import re, sys

if len(sys.argv) < 2:
	sys.exit('Program se poziva sa %s -[acig] naslov_knjige' % sys.argv[0])

autor   = False
godina  = False
izdavac = False
cena    = False
naslov  = None

if re.match(r'-[aicg]+', sys.argv[1] ) :    
  if 'a' in sys.argv[1]:
    autor = True
  if 'c' in sys.argv[1]:
    cena = True
  if 'g' in sys.argv[1]:
    godina = True  
  if 'i' in sys.argv[1]:
    izdavac = True

  if len(sys.argv) >2:   
    naslov = sys.argv[2]  
  else:
    sys.exit("Jedan od argumenata mora biti naslov knjige")  
elif sys.argv[1][0] == '-' :
		sys.exit('Nepodrzana opcija')
else: # nije opcija 
  naslov = sys.argv[1]

try:
  with open("knjige.xml","r") as f:
    sadrzaj = f.read()
except IOError:
  exit('Neuspesno otvaranje datoteke knjige.xml')
  
#print( sadrzaj)  

re_knjiga = re.compile( r'<knjiga\s+rbr\s*=\s*"(?P<rbr>[1-9]\d*)"\s*>\s*' 
  + r"(?=.*?<naslov>\s*(?P<naslov>.*?)\s*</naslov>)"
  + r"(?=.*?<autor>\s*(?P<autor>[A-Z][a-z]+(?:\s+[A-Z][a-z]+)+)\s*</autor>)"
  + r"(?=.*?<izdavac>\s*(?P<izdavac>.*?)\s*</izdavac>)"
  + r"(?=.*?<godina_izdanja>\s*(?P<godina>[12]\d{3})\s*</godina_izdanja>)"
  +r'(?=.*?<cena\s+valuta\s*=\s*"(?P<valuta>rsd|eur)">\s*(?P<cena>[1-9][0-9]*)\s*</cena>)'
  + r".*?"
  + r'</knjiga>',re.S)

katalog = {}
#rbr -> [naslov, autor, izdavac, godina, cena, valuta]
for m in re_knjiga.finditer(sadrzaj):
  katalog[m.group('rbr')] =  [m.group('naslov'), m.group('autor'),
                              m.group('izdavac'), m.group('godina'),
                              m.group('cena'), m.group('valuta')]
  #print( m.groups(), '\n\n')
  
for k,v in katalog.items():
  #print( k, v)
  if v[0] == naslov:
    podaci = v[1:] # [autor, izdavac, godina, cena, valuta]
    
    if autor :
      print( "Autor:", podaci[0])
    if izdavac:
      print( "Izdavac:",podaci[1])
    if godina:
      print("Godina izdanja:", podaci[2])
    if cena:
      print( "Cena:", podaci[3],podaci[4])
    
    if not(autor or izdavac or godina or cena):
      for info in podaci:
        print( info, end=" ")
        
    print( '\n')    
    
