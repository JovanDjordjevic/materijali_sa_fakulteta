# Skript prati linkove navedene u HTML datoteci  i vodi evidenciju o datotekama koje su posecene
import sys, re

def obradi_datoteku(ime_datoteke):
  if(ime_datoteke in obradjene_datoteke):
    return
  
  obradjene_datoteke.append(ime_datoteke)
  
  try:
    with open(ime_datoteke,"r") as f:
      datoteka = f.read() # linijska obrada datoteke ne bi bila dobra 
  except IOError:
    exit("Neuspelo otvaranje '" + ime_datoteke + "'")
    
  ri=re.compile(r'<a\s+href\s*=\s*"(.*?)">.*?</a>', re.I | re.S)  
  
  for m in ri.finditer(datoteka):
    obradi_datoteku(m.group(1))


if len(sys.argv) > 1:
  pocetna = sys.argv[1] 
else: 
  pocetna = "index.html"

obradjene_datoteke = []
obradi_datoteku(pocetna);

for datoteka in obradjene_datoteke:
  print( datoteka )

  
