import sys,re

if len(sys.argv)!=3 and len(sys.argv)!=4:
	exit("br args")

if re.fullmatch(r".*\.csv",sys.argv[1]) is None:
	exit("ekstenzija")

opcija=''
KLUB='' 

if sys.argv[1]=='-g':
	opcija='-g'
else:
	opcija='-t'
	KLUB=sys.argv[2]


try:
	f=open(sys.argv[1],"r")
except IOError:
	exit("io")

ri=re.compile(r"^(?P<ime>[A-Z][a-z]+\s*([A-Z][a-z]+|[a-z]+)?\s*([A-Z][a-z]*)?),"
+r"\s+(?P<drzava>[A-Z][a-z]*),"
+r"\s+(?P<golovi>[1-9][0-9]*),"
+r"\s+(?P<utakmice>[1-9][0-9]*),"
+r"\s+(?P<g1g2>(?P<g1>[1-9][0-9]{3})-(?P<g2>[1-9][0-9]{3})?),"
+r"\s+(?P<lista_klubova>([A-Z][A-Za-z0-9, ]+)+)"
)

igraci=[]

for linija in f.readlines():
	reg=ri.search(linija)
	if reg is not None:
		#print(reg.group('ime')+' '+reg.group('drzava')+' '+reg.group('golovi')+' '+reg.group('utakmice')+' '+reg.group('g1g2')+' '+reg.group('lista_klubova'))
		tup=(reg.group('ime'),reg.group('drzava'),reg.group('golovi'),reg.group('utakmice'),reg.group('g1g2'),reg.group('lista_klubova'))	
		igraci.append(tup)

print(igraci)
		
if opcija=='-g':
	igraci.sort(reverse=True,key=lambda x: int(x[2])/float(x[3]))
	print(igraci)
	for i in igraci:
		print(i[0] + str(int(i[2])/float(i[3])))		
	
	
	
