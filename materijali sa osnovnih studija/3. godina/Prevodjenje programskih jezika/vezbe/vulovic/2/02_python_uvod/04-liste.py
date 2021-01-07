# a je tipa ntorka navedenih elemenata  (eng. tuple)
# Moze se definisati i bez zagrada ()
a = (1,2,3,4,5)
print( a )
print(type(a))

# Sa ntorkama mozemo sve sto smo mogli sa niskama
# I za njih vazi da ne mozemo menjati elemente, kao niskama karaktere

# Kreiramo listu od ntorke u kojoj su nabrojani elementi
l = list((1,2,3,4,5))
# Isto se postize i sledecom naredbom jer je u zagradi ista sekvenca kao i a
l1 = list(a) 

# Prikazujemo listu l i za njom l1
print( l, l1 )

# Kreiramo novu listu u kojoj nisu svi elementi celi brojevi 
l2 = [7.2, 4, 'seminar', 'Python', 'programiranje']
print( l2 )

# Menjamo element na indeksu 2
l2[2] = 'uvod'
print( l2 )

# Stampamo rezultat nadovezivanja dve liste
print( l1 + l2 )


# Na liste mozemo primeniti indeksnu notaciju da izdvojimo pojedinacni element 
# ili vise uzastopnih

# Pravimo kopiju liste l1 i cuvamo je u promenljivu b
b = l1[:]
print( b )

# Zamenjujemo elemente liste b pocevsi od elementa sa indeksom 3,
# pa do kraja liste, praznom listom. 
# Drugim recima iz liste b uklanjamo sve pomenute elemente
b[3:] = []
print( b )

# l1 je nepromenjena jer smo radili sa kopijom
# Ukoliko u 32. redu sklonite [:] iz naredbe b = l1[:] primeticete razliku.
print( l1 )

# Nadovezujemo b listu sa samom sobom i prikazujemo rezultat nadovezivanja. 
# Lista b ostaje nepromenjena.
print( b*2 )

# Dodajemo na pocetak liste b listu od 2 elementa
b[:0]=['na','pocetak']
print( b )


# Dodajemo u listu b izmedju 2. i 3. elementa  2 elementa 
b[2:2] = ["nesto","izmedju"]

# Nadovezujemo listu b sa listom l2
# Isto bi se moglo postici sledecom naredbom: 
# b = b + l2
b.extend(l2)
print( b )
 
# Dodajemo na kraj liste nov element koji je lista l
b.append(l)
print( b )

# Stampamo 1. element liste koja dodata na kraj liste b
print( b[-1][0])

# Uklanjanje konkretnog elementa liste je moguce samo ako je element vec u listi
# Inace, imacemo ValueError.
if 'pocetak' in b:
  b.remove('pocetak')
else:
  print("'pocetak' se ne nalazi u listi " + b)

# Uklanjamo poslednji element liste i stampamo ga.
print( b.pop() )
print( b )

# Uklanjamo element na indeksu 0.
print( b.pop(0) )
print( b )

# obrcemo listu b i stampamo je pre i posle te modifikacije
print( b )
b.reverse()
print( b )

# Sledece naredbe ponovo imaju smisla samo ako element vec postoji u listi. 
# Ukoliko element nije u listi, imacemo ValueError.
# Prikazujemo indeks elementa sa vrednoscu 'uvod'.
print( b.index('uvod') )

# Broj pojavljivanja reci 'uvod' u listi b
print( b.count('uvod') )

# Uklanjamo 4 elementa liste pocevsi od elementa na indeksu 3.
b[3:7] = []
print( b )

# Sortiramo listu b u opadajucem  poretku. Ona nakon brisanja sadrzi samo niske
# i poredjenje je leksikografsko.
b.sort(reverse=True)
print( b )

# Sortiramo listu niski po duzini opadajuce
# Kada koristimo imena argumenata prilikom poziva funkcije nije bitan redosled
# navodjenja argumenata.
# key parametar je funkcija poredjenja koja ce se primeniti na jedan element liste b
b.sort(key=len, reverse = True)
print( b )

# Za slozenija poredjenja moze se koristiti lambda izraz.
b.sort(key=lambda x: len(x), reverse = True)
print( b )
