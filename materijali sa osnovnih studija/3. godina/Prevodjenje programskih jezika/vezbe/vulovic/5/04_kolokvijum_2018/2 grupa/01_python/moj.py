import sys,re

opcija=''
NAZIV=''

if len(sys.argv)!=2 and len(sys.argv)!=3:
	exit("args")

if len(sys.argv)==2:
	opcija=sys.argv[1]

if len(sys.argv)==3:
	opcija=sys.argv[1]
	opcija=sys.argv[2]

try:
	f=open("igre.xml","r")
except IOError:
	exit("io")


data=f.read()

ri=re.compile(r"<igra .*?>(.*?)</igra>",re.S)

lista_igara=[]

for i in ri.finditer(data):
	if i is not None:
		#print(i.group(1))
		lista_igara.append(i.group(1))

#print(lista_igara)

naz=re.compile(r"<naziv>(?P<naziv>[A-Za-z0-9.,():' ]+)</naziv>",re.S)
god=re.compile(r"<godina>(?P<godina>19[5-9][0-9]|20[0-1][0-8])</godina>",re.S)
izd=re.compile(r"<izdavac>(?P<izdavac>([A-Z0-9][A-Za-z0-9]+\s?)+)</izdavac>",re.S)
pla=re.compile(r"<platforme>(?P<platforme>((PlayStation|Xbox|Nintendo|PC), )*(PlayStation|Xbox|Nintendo|PC))</platforme>",re.S)
oce=re.compile(r"<ocena>(?P<ocena>([0-9]\.[0-9])|10)</ocena>",re.S)
	
igrice=[]

for i in lista_igara:
	sadrzaj=[]
	n=naz.search(i)
	#print(n.group(1))
	g=god.search(i)
	#print(g.group(1))
	iz=izd.search(i)
	#print(iz.group(1))
	p=pla.search(i)
	#print(p.group(1))
	o=oce.search(i)
	#print(o.group(1))
	if n is not None and g is not None and iz is not None and p is not None and o is not None:
		sadrzaj.append(n.group(1))  #0
		sadrzaj.append(g.group(1))  #1	
		sadrzaj.append(iz.group(1)) #2	
		sadrzaj.append(p.group(1))  #3	
		sadrzaj.append(o.group(1))  #4	
		igrice.append(sadrzaj)


if opcija=='-sve':
	igrice.sort(key=lambda x: x[0])
	for i in igrice:
		print(i[0])
if opcija=='-info':
	for i in igrice:
		if sys.argv[2] in lower(i[0]):
			print(i[0]+" "+str(i[4]))
if opcija=='-i':
	for i in igrice:
		if NAZIV==i[2]:
			print(i[0]+" "+i[1])


