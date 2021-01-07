#pocetno stanje
pocetno = 0
#lista zavrsnih stanja
zavrsna = (1,2)

#matrica prelaza automata
prelaz = { 0: {'a':1, 'c':2}, 
          1: {'b':1, 'c':2 }, 
          2: {'a':1, 'b':2, 'c':0} }

stanje = pocetno

while True:
  try:
    c = input()
    #proveravamo da li je uneto slovo azbuke
    if c != 'a' and c != 'b' and c !='c' :
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
    exit('Podrzana su a b c u zapisu' + c)
 
#ukoliko je automat u zavrsnom stanju na kraju ulaza, rec je prihvacena
if stanje in zavrsna:
  print('Automat prihvatio rec')
else:
  print('Rec nije prihvacena')
