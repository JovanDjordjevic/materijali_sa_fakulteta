# Prvi primer koji prikazuje linije sa ponovljenim recima 
# u datoteci koja se zadaje kao argument komandne linije
import sys
import re

ri=re.compile(r"(?i)(\b[a-zA-z]+\b)\s+\1")

if len(sys.argv) == 1:
  exit('Program se poziva sa %s ime_datoteke' %sys.argv[0])
  
m = re.search(r'.*\.txt',sys.argv[1])
if m is None:
  exit('Zahteva se .txt datoteka')
  
try:
  f= open(sys.argv[1],"r+")
except IOError:
  exit('Neuspelo otvaranje datoteke: ', sys.argv[1])
  
# drugi nacin bi bio
# for linija in f.readlines():
for linija in f:
  match=ri.search(linija)
  if match is not None:
    print( "Poklapanja: %s\t groups = %s" %(match.group(),match.groups()) )
    print( "Linija bez ponavljanja: " + ri.sub(r'\1',linija) )
  
f.close()  
