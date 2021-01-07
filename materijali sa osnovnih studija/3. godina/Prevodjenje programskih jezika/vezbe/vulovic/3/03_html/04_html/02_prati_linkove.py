# Skript obradjuje html datoteke dostupne iz polazne html datoteke
# (preko linkova) i racuna popularnost svake od datoteka, na osnovu
# broja linkova
import re

def obradi_datoteku(ime_datoteke):
  if (ime_datoteke in obradjene_datoteke):
    return

  #print( "Obradjujem datoteku: " + ime_datoteke )
  obradjene_datoteke.append(ime_datoteke)
  
  try:
    with open(ime_datoteke,'r') as f:
      dat = f.read()
  except IOError:
    exit('Neuspelo otvaranje datoteke ' + ime_datoteke)
    
  ri=re.compile(r'<a\s+href\s*=\s*"([^"]+)">(.*?)</a>', re.I | re.S) 
  for m in ri.finditer(dat):
    tekst = m.group(2)
    url = m.group(1)
    #tekst = re.sub('\s+',' ',tekst)

    #print( "Pronadjen link: " + tekst +" [" + url + "]\n")
    if url not in popularnost:
      popularnost[url] = 1
    else:
      popularnost[url] += 1
    obradi_datoteku(url)
    

obradjene_datoteke = []
popularnost = {}
obradi_datoteku("prva.html")

#radi u Python 3.6
#popd= OrderedDictionary(sorted(popularnost.items(), reverse=True, key=lambda t:t[1]))

popd = list(popularnost.items())
popd.sort(reverse=True, key=lambda t: t[1])

for no, url in popd:
  print( url, "\t" , no)

