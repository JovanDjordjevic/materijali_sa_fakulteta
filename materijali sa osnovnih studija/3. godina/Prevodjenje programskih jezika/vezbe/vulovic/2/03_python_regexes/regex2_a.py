# Prvi primer koji prikazuje linije sa ponovljenim recima 
# u TXT datoteci koja se zadaje kao argument komandne linije

import sys 
import re

if len(sys.argv)==1:
	exit("Nedostaje datoteka kao argument komnadne linije")
	
m = re.fullmatch(r".+\.txt", sys.argv[1])	

if m  is None:
	exit("Datoteka mora biti ekstenzije .txt")

datoteka = ""
try: 	
	#f = open(sys.argv[1],"r")	
	#datoteka = f.read()
	#f.close()
	
	# kada nam je datoteka potrebna zbog malog skupa jednostavnih radnji
	with open(sys.argv[1],"r") as f:
		datoteka = f.read()
except IOError:
	exit("Neuspelo otvaranje datoteke"+sys.argv[0])
	
#print datoteka	
for m in re.finditer(r"\b(\w+)\s+\1",datoteka, re.I):
	print( m.group() )
	
	
