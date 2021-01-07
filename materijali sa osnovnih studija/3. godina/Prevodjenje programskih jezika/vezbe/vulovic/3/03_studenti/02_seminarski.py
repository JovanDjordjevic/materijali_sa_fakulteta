# Direktorijum cije se ime navodi kao prvi argument komandne linije programa sadrzi 
# poddirektorijume nazvane po indeksima studenta I smera. Direktorijumi sadrze zadatke
# koje su studenti tokom leta radili u datotekama oblika broj.ext gde ext ukazuje na 
# programski jezik u kome je zadatak radjen (C, C++, JAVA, Pascal). Napisati skript
# koji tabelarno prikazuje zadatke koje je svaki student radio. 

import os, sys, re

if len(sys.argv) > 1:
  homedir = sys.argv[1]
else:
  homedir = '.'

re_dir = re.compile(r'^m[mnvrli]\d{5}$')
re_file = re.compile(r'(\d)\.(?:java|pas|c|cpp)$')

for f in os.listdir(homedir):
  dirpath = os.path.join(homedir,f)
  m = re_dir.match(f)
  if os.path.isdir(dirpath) and m is not None:
    print( "\n" + m.group() , end =' ' )
    # izdvajamo zadatke koje student uradio
    for sf in os.listdir(dirpath):
      pathname = os.path.join(dirpath,sf)
    #  print "\t " + pathname
      if os.path.isfile(pathname):
      # ako je datoteka ekstenzije .c ili .cpp ili .pas ili .java
        m = re_file.match(sf) 
        if m is not None:
          print( "\t", m.group(1), end =' ')
          
  #sve ostale tipove preskacemo

print("\n")
