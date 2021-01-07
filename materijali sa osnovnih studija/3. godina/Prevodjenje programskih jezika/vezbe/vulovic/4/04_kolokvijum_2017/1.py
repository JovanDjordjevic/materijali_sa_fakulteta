import re, sys

if len(sys.argv) <3:
  exit('Nedovoljno argumenata')
  
gol = False
ekipa = False
klub = ""

for a in sys.argv[2:] :
  if( a == "-g") :
    gol = True
  elif( a == "-t"):
    ekipa = True
  elif ekipa == True:
    klub = a
  else:
    exit('Neispravan argumente'+a)


if( re.match(r"^.*\.csv$",sys.argv[1]) == None):
    exit(sys.argv[1]+"nijje csv ")
    
    
igraci = []

try:
  with open(sys.argv[1],"r") as f:
    datoteka = f.readlines()
except IOError:
    exit('Neispravno otvaranje datoteke')


reg = re.compile(r"^([A-Z][a-z]+\s*(?:[A-Za-z]*\s+[A-Z][a-z]*)?)"
        r",\s*[A-Z][a-z]+,\s*(0|[1-9]\d*)"
        +r",\s*(0|[1-9]\d*),\s*(\d{4})-(\d{4})?,"
        +r"\s*([A-Z][a-zA-Z\d]+[ a-z\dA-Z]*(?:,\s*[A-Z][a-z\d]+[ a-z\dA-Z]+)*)")
                 
for linija in datoteka:
  m = reg.search(linija) 
  if m is not None:
    #print m.groups()
    igraci.append(m.groups())


if gol :
  igraci.sort(reverse = True, key= lambda x: int(x[1])/float(x[2]))
  for i in igraci:
    print "%s %.2f" %(i[0], int(i[1])/float(i[2]))
          
elif ekipa:
  for i in igraci:
    if klub in i[5]:
      print i[0], i[3], 
      if(i[4] is not None):
        print int(i[4]) - int(i[3])
      else:
        print 2018 - int(i[3])
