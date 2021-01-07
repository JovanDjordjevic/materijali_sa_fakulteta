# Program implementira automat koji prepoznaje ulaz sa parnim brojem 0
# U mapi se cuva matrica prelaza, pri cemu se za kljuc mape uzima par (stanje, slovo)

stanje = 'P'
zavrsno ='P'

#matrica prelaza
prelaz ={('P','0'):'N', ('P','1'):'P', ('N', '0'): 'P', ('N','1'):'N' }

print ('Unesite 0 ili 1: ')
while True:
  try:
    c = input()
    if (c != '0' and c !='1' ):
      raise ValueError('Nije uneta ni 0 ni 1')
  except EOFError:
    break
  except ValueError as e:
    print( e )
    exit()
    
  # smemo ovako jer je automat potpun 
  # i imamo prelaze iz svakog stana po svakom slovu
  # da je nepotpun bilo bi  dodata provera u if i else grana potom
  # if (stanje,c) in prelaz:
  stanje = prelaz[(stanje,c)]
  # else:
  #  exit("Ne postoji prelaz iz " + stanje + " po slovu " + c)
  
  print( "\t" + stanje)
 
if stanje == zavrsno :
  print ('Rec ima paran broj nula')
else:
  print ('Rec nije prihvacena automatom')
