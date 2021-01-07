import json
import sys

class Player:
    def __init__(self, dres, ime, prezime, visina, godine, pozicija):
        self.dres = dres
        self.ime = ime
        self.prezime = prezime
        self.visina = visina
        self.godine = godine
        self.pozicija = pozicija

    def getVisina(self):
        return self.visina
    
    def getGodine(self):
        return self.godine

    def getPozicija(self):
        return self.pozicija

    def __str__(self):
        return str(self.dres) +" "+ self.ime +" "+ self.prezime +" "+ str(self.visina) +" "+ str(self.godine) +" "+ str(self.pozicija)
    
        

if len(sys.argv) != 2:
    print("-1")
    exit(1)

godine = float(input())
pozicija = int(input())

if pozicija not in [1,3,5]:
    print("-1")
    exit(1)

with open(sys.argv[1],"r") as f:
    data = json.load(f)

kosarkasi = []

for kosarkas  in data:
    #print(kosarkas)
    poz = -1
    if kosarkas['visina'] > 200:
        poz = 5
    elif kosarkas['visina'] < 190:
        poz = 1
    else:
        poz = 3

    kosarkasi.append( Player( kosarkas['dres'], kosarkas['ime'], kosarkas['prezime'], kosarkas['visina'], kosarkas['godine'], poz ) )

for k in kosarkasi:
    print(k)

maxVisina = -1
for k in kosarkasi:
    if k.getGodine()<= godine and k.getPozicija() == pozicija:
        if k.getVisina() > maxVisina:
            maxVisina = k.getVisina()

print(maxVisina)

