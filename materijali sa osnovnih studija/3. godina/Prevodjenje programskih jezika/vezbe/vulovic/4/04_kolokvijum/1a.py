# Napisati python-skript koji kao prvi argument komandne linije prihvata
# ime fajla koji je dobijen sistemom UNITEX kao rezultat prepoznavanja
# imenovanih entiteta. Na osnovu tog fajla treba napraviti .xml fajl koji 
# je dobijen zamenom semantičkih markera odgovarajućim tagom (+org se menja tagom <org>).


import re, sys

if len(sys.argv ) ==1 :
	exit('Potrebna je stn datoteka kao argument')

if re.fullmatch(r'.*\.stn',sys.argv[1]) is None:
	exit('Nije poslata .stn datoteka')
	
try:
	with open(sys.argv[1],"r") as f:
		datoteka = f.read()
except IOError :
	exit('Neuspelo otvaranje i citanje')
	
#{Skoplja,.NE+city:2q}.	
izraz = re.compile(r'{(.*?),\.NE\+([a-z]+):.*?}')	

izlaz = izraz.sub(r'<\2>\1</\2>',datoteka)

try:
	with open(re.sub('\.stn$','.xml',sys.argv[1]),"w") as f:
		f.write("<xml>\n" + izlaz + "\n</xml>")
except IOError:
	exit('Neuspelo otvaranje i pisanje')
