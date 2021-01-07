# Direktorijum cije se ime navodi kao prvi argument komandne linije programa sadrzi 
# poddirektorijume nazvane po indeksima studenta I smera. Direktorijumi sadrze zadatke
# koje su studenti tokom leta radili u datotekama oblika broj.ext gde ext ukazuje na 
# programski jezik u kome je zadatak radjen (C, C++, JAVA, Pascal). Napisati skript
# koji tabelarno prikazuje zadatke koje je svaki student radio. 

# Na primer
# Pera Peric      - pas - c
# Ivan Ivanovic   c pas - java



import os, sys, re

# izdvajamo indekse studenata iz datoteke koja sadrzi informacije o studentima u formatu
# mr09114, Ivan Ivanovic
# mv05023, Marko Markovic


if len(sys.argv) > 1:
  homedir = sys.argv[1]
else:
  homdir = '.'

studenti={}

# homedir+'/indeksi' bi bilo na Linux-u
putanja = os.path.join(homedir, 'indeksi')

try:
  #nakon zavrsetka ovog bloka automatski se izvrsava indeksi.close()
  with open(putanja, 'r') as indeksi:
    for linija in indeksi.readlines():
      # izbacujemo karakter \n
      #if linija[-1] =='\n':
       # linija=linija[0:-1]
      if re.match(r"m[mnvlri]\d{5},\s*[A-Za-z ]+", linija) is not None:  
        info = re.split(r',\s*|\n',linija)
        studenti[info[0]]=info[1]    #kao studenti['indeks']='ime'
except IOError:
  sys.stderr.write("Nema datoteke sa indeksima\n")
  exit()

#print studenti  
  
# objekti za regularne izraze 
# za indeks studenta
re_dir=re.compile(r'^m[mnvlri]\d{5}$')
# za naziv datoteke sa kodom
re_file=re.compile(r'(\d+)\.(java|pas|c|cpp)$')

max_br_zadatka = 0
zadaci = {}

#listamo direktorijum sa studentskim direktorijumima
for f in os.listdir(homedir):
  #stud_dir_path = homedir + "/" +f # radilo bi pod Linux-om
  stud_dir_path = os.path.join(homedir,f)
  #print( stud_dir_path)
  m = re_dir.match(f)
  # ako je direktorijum i naziv odgovara studentskom indeksu i u pitanju je student koji je sa spiska
  if os.path.isdir(stud_dir_path) and m is not None  and m.group() in studenti:  
    student_indeks = m.group()
    #print( student_indeks + "--------------" )
    # izdvajamo zadatke koje student uradio
    for sf in os.listdir(stud_dir_path):
      zadatak_path = os.path.join(stud_dir_path, sf)
      # ako je datoteka ekstenzije .c ili .cpp ili .pas ili .java
      m = re_file.match(sf) 
      if os.path.isfile(zadatak_path) and  m is not None:
        zadatak = int(m.group(1))
        if zadatak > max_br_zadatka:
          max_br_zadatka = zadatak
        zadaci[(student_indeks, zadatak)] = m.group(2)


# prikazujemo tabelu oblika
# Pera Peric - pas - c
# Ivan Ivanovic c pas - java

for indeks,ime in studenti.items():
  print( ime + "  ", end =' ')
  for i in range(1, max_br_zadatka+1):
    
    if (indeks, i) not in zadaci:
      print( "\t-", end =' ')
    else:
      print( "\t" + zadaci[(indeks, i)], end =' ')     
  print ("\n")
