# Napisati python-skript koji kao prvi argument komandne linije prihvata
# ime fajla koji je dobijen sistemom UNITEX kao rezultat prepoznavanja
# imenovanih entiteta. Na osnovu tog fajla treba napraviti .xml fajl koji 
# je dobijen zamenom semantičkih markera odgovarajućim tagom (+org se menja tagom <org>).

import re
import sys

if len(sys.argv)!=2:
	exit('Program se poziva sa: python '+sys.argv[0] + " STN datoteka")
if re.fullmatch(r"[\w_-]+\.stn",sys.argv[1]) is None:  
	exit('Prosledjena datoteka mora biti ekstenzije .stn!')

try:
	with open(sys.argv[1],"r") as f:
		fajl = f.read()
except IOError:
	exit('Neuspelo otvaranje i citanje datoteke ' +sys.argv[1] )
	
	
uzorak=re.compile(r'{(.*?),\.NE\+([a-z]+):[0-9][a-z]}',re.S)

zamena = uzorak.sub(r"<\2>\1</\2>", fajl)
 
try:
	with open(sys.argv[1][:-3]+"xml","w") as fxml:
		fxml.write("<xml>\n")
		fxml.write(zamena)
		fxml.write("\n</xml>")
		
except IOError:
	exit('Neuspelo otvaranje i citanje datoteke jat.xml')	
