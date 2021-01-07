# Program implementira automat koji odgovara regularni izraz 
# (ab?)+(b?a+b)*



# U mapi se cuva matrica prelaza, pri cemu se za kljuc mape uzima 
# stanje, a vrednost je ponovo mapa oblika slovo->novo_stanje

# Nakon primene algoritma Gluskova da dobijemo automat, potom postupka
# determinizacije i minimizacije dobija se MDKA sa sledecemo tablicom 

prelaz = { 'A': {'a': 'BC'},
          'BC': {'a': 'BC', 'b': 'DE'},
          'DE': {'a': 'BC', 'b': 'F'}, 
          'F' : {'a': 'G'}, 
          'G' : {'a': 'G', 'b': 'H'},
          'H' : {'a': 'G', 'b': 'F'} }

#pocetno stanje
pocetno = 'A'
#lista zavrsnih stanja
zavrsna = ('BC','DE','H')

stanje = pocetno

rec = input('Unesite celu rec:')

for c in rec:
  try:
    #proveravamo da li je uneto slovo azbuke
    if c != 'a' and c != 'b':
      raise ValueError
   
    #ukoliko imamo prelaz po unetom slovu iz trenutnog stanja automata
    #automat prelazi u novo/staro stanje
    #inace imamo gresku
    if c in prelaz[stanje]:
      stanje = prelaz[stanje][c]
    else:
      exit('Rec ne moze biti prihvacena automatom')
      
    #Ispisujemo trenutno stanje automata  
    print('\tStanje: ', stanje)  
  except EOFError:
    break
  except ValueError:
    exit('Podrzana su slova (a, b) u zapisu, ali nije '+ c)
 
#ukoliko je automat u zavrsnom stanju na kraju ulaza, rec je prihvacena
if stanje in zavrsna:
  print('Automat prihvatio rec')
else:
  print('Rec nije prihvacena')
