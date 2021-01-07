import sys,re


bean=''
opcija=''

if len(sys.argv)==2:
	bean=sys.argv[1]
	opcija='sve'

if len(sys.argv)==3:
	bean=sys.argv[2]
	opcija=sys.argv[1]


try:
	f=open('knjige.xml',"r")
except IOError:
	exit("beans")

data=f.read()
f.close()

lista_knjiga=[]

knjiga=re.compile(r"<knjiga.*?>(.*?)</knjiga>",re.S)

for k in knjiga.finditer(data):
	lista_knjiga.append(k.group())

#print(lista_knjiga[0])
#print()
#print(lista_knjiga[1])

nas=re.compile(r"<naslov>\s*(?P<naslov>[A-Za-z ]+)\s*<\/naslov>",re.S)
aut=re.compile(r"<autor>\s*(?P<autor>[A-Za-z ]+)\s*<\/autor>",re.S)
cen=re.compile(r"<cena\s*valuta=\"(eur|rsd)\"\s*>\s*(?P<cena>[0-9]+)\s*<\/cena>",re.S)
izd=re.compile(r"<izdavac>\s*(?P<izdavac>[^0-9]+)\s*<\/izdavac>",re.S)
god=re.compile(r"<godina_izdanja>\s*(?P<godina>[0-9]{4})\s*<\/godina_izdanja>",re.S)

knjige=[]


for k in lista_knjiga:
	sadrzaj=[]
	n=nas.search(k)
	a=aut.search(k)
	c=cen.search(k)
	i=izd.search(k)
	g=god.search(k)
	if n!=None and a!=None and c!=None and i!=None and g!=None:
		sadrzaj.append(n.group(1))	#0
		sadrzaj.append(a.group(1))	#1		
		sadrzaj.append(c.group(1))	#2
		sadrzaj.append(i.group(1))	#3
		sadrzaj.append(g.group(1))	#4
		knjige.append(sadrzaj)

print(knjige)



for k in knjige:
	for i in k:
		if (i[0]==bean):
			if(opcija=='-a'):
				print(i[1])
			elif(opcija=='-c'):
				print(i[2])
			elif(opcija=='-i'):
				pritn(i[3])
			elif(opcija=='-g'):
				print(i[4])
			else:		 	
				print(i)
	

