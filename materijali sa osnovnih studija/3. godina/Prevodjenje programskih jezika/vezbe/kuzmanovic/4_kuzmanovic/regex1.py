#!/usr/bin/python3

import sys, re

# Kreiramo neku poruku, bilo kakvu
poruka = "Danas je divan dan"
# u poruci poklapamo sve reci redom u ignore case modu
matcher = re.match(r"(?i)(\w+\s*)+", poruka);

# BITNO:
# re.match metod radi tako sto pokusava da poklopi sablon sa sadrzajem recenice
# i to uvek radi iskljucivo od pocetka recenice.
# Najcesce, match se koristi samo onda kada treba poklopiti sadrzaj stringa u postpunosti
# (provera ekstenzije, provera bukvalnog imena itd).


# ako je poklapanje uspesno, prikazujemo poklapanje korisniku
if matcher is not None:
	print(matcher.group())
else:
	# inace stampamo poruku o neuspehu
	print("Sablon se ne nalazi u tekst")

# BITNO:
# re.search metod radi tako sto pokusava da pponadje prvo poklopanje sablona sa sadrzajem recenice
# i uvek trazi samo prvo poklapanje. Za sledece poklapanje, neophodno je ponovo pozvati search metod, 
# ali treba voditi racuna da pretraga treba da restartuje od prvog neobradjenog karaktera a ne ponovo od
# pocetka stringa

# Trazimo rec koja pocinje da slovo d u poruci i to u single line modu
m = re.search(r"\bd([a-z]+)", poruka, re.S);

# BITNO:
# single line mod tumaci ceo sadrzaj poruke kao jedan jedini red. Posledica ovoga je 
# da operator tacka u regex-u jede i nove redove

# ako je poklapanje uspelo
if m is not None:
	print(m.group())					# stampamo komletno poklapanje
	print(poruka[m.start():m.end()])	# sto mozemo i na ovaj nacin
	print(m.group(1))					# stampamo prvu grupu u regex-u, tj. ono sto odgovora \1 bek referenci
	print(m.groups())					# stampamo listu svih grupa u regex-u
	
# trazim sledecu rec koja pocinje na d. 
# BITNO:
# obratiti paznju na pomeranje offseta u poruci. Pretragu restartujem od prvog
# neobradjenog karaktera		
m = re.search(r"\bd([a-z]+)", poruka[m.end():], re.S);

# ako je poklapanje uspelo, ponovo stampamo isto
#if m is not None:
#	print(m.group())
#	print(poruka[m.start():m.end()])
#	print(m.group(1))
#	print(m.groups())
	
# za pronalazenje svih poklapanja koristi se metod findall. povratna vrednost metoda je 
# lista svih poklapanja
reci = re.findall(r'(?i)\b(d([a-z]+))', poruka);

print(reci)

# re modul i metod sub rade kao sed alat u global modu
print(re.sub(r'(?i)\b(d([a-z]+))', r'\2-\1', poruka));

# replace je moguc i pomocu replace metoda definisanim nad string tipom podataka
# replace metod je znatno manje fleksibilan u odnosu na re.sub
print(poruka.replace("Danas", "Sutra"))

# BITNO:
# metodi iz re modula se na ovaj nacin koriste samo onda kada vam treba jednokratno i brzinsko poklapanje
# regularnih izraza. Za bilo koje slozenije poklapanje ili komplikovaniju logiku u programu koriste se
# kompajlirani regularni izrazi
