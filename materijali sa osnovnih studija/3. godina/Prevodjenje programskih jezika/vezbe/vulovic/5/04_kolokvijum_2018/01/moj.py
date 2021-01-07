#! usr/bin/env python3

import sys,re

opcija=''
NAZIV=''

if len(sys.argv)!=2 and len(sys.argv)!=3:
	exit("arg")

if len(sys.argv)==2:
	opcija=sys.argv[1]
else:
	opcija=sys.argv[1]
	NAZIV=sys.argv[2]

try:
	f=open("paketi.xml","r")
except 	IOError:
	exit("io")

data=f.read()
f.close()

paket=re.compile(r"<paket .*?>(.*?)<\/paket>",re.S)

lista_paketa=[]

for p in paket.finditer(data):
	if p is not None:
		#print(p.group(1))
		lista_paketa.append(p.group(1))

#print(lista_paketa)

naz=re.compile(r"<naziv>(?P<naziv>.*?)</naziv>",re.S)
ver=re.compile(r"<verzija>(?P<verzija>[0-9]+\.[0-9]+\.[0-9]+)</verzija>",re.S)
opi=re.compile(r"<opis>(?P<opis>.*?)</opis>",re.S)
rep=re.compile(r"<repo>(?P<repo>github|gitlab|bitbucket)</repo>",re.S)
veb=re.compile(r"<veb>(?P<veb>(www\.)?([A-Za-z0-9]+\.)+(org|com))</veb>",re.S)

paketi=[]
for p in lista_paketa:
	sadrzaj=[]
	n=naz.search(p)
	#print(n.group())
	v=ver.search(p)
	#print(v.group())
	o=opi.search(p)
	#print(o.group())
	r=rep.search(p)
	#print(r.group())
	ve=veb.search(p)
	#print(ve.group())
	#print()
	if n is not None and v is not None and o is not None and r is not None and ve is not None:
		#print(n.group('naziv') + " " +v.group('verzija') + " " +o.group('opis') + " " +r.group('repo') + " " +ve.group('veb') + " " )
		sadrzaj.append(n.group('naziv'))    #0
		sadrzaj.append(v.group('verzija'))  #1	
		sadrzaj.append(o.group('opis'))     #2
		sadrzaj.append(r.group('repo'))     #3
		sadrzaj.append(ve.group('veb'))     #4
		paketi.append(sadrzaj)

#print(paketi)
#print()

if opcija=='-a':
	paketi.sort(key=lambda x: x[0])
	print(paketi)

if opcija=='-v':
	for p in paketi:
		if p[0]==NAZIV:
			print(p[1])

if opcija=='-w':
	for p in paketi:
		if p[0]==NAZIV:
			print(p[4])
if opcija=='-r':
	for p in paketi:
		if p[0]==NAZIV:
			print(p[3])
if opcija=='-o':
	for p in paketi:
		if p[0]==NAZIV:
			print(p[2])
	



