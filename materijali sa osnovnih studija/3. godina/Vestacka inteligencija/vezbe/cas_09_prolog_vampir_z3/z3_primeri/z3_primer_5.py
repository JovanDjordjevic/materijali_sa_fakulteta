from z3 import *

    # Dve nemimoilazne prave se seku ili su paralelene.
    # Prave koje se seku leže u istoj ravni.
    # Prave koje su paralelene leže u istoj ravni.
    # Dve nemimoilazne prave leže u istoj ravni.            # tretiracemo ovo kao konjekturu, a recenice iznad kao aksiome

# posto je z3 samo API ka solveru, za neke ovakve primere ce biti malo vise kucanja. Posto smo ranije ovaj zadatak resili
# tako sto su nams vi prediakti bili oblika p(x,y), posmatracemo to kao neku funkciju koja uzima 2 prave i slika ih u bool
# moramo za ovu "funkciju" napraviti nase domene
# (P, P) -> B

B = BoolSort()
P = DeclareSort('Prava')

# poslednje sto se navede je kodomen, neka torka pre toga je domen
nm = Function('nm', P, P, B)  # nemimoilazne
s = Function('s', P, P, B)    # seku se
p = Function('p', P, P, B)    # paralelne su   
r = Function('r', P, P, B)    # u istoj su ravni

solver = Solver()

# posto nase funkcije barataju sa pravama, promenljive koje koristimo takodje treba da pripadaju tom skupu
x, y  = Consts('x y', P)
# damo skup aksioma (mozemo to kao neki niz npr)
# kada prosledimo nesto kao niz, to se u z3 vodi kao niz konjukcija
axioms = [
            ForAll( [x,y], Implies(nm(x,y), Or(s(x,y), p(x,y))) ),
            ForAll( [x,y], Implies(s(x,y), r(x,y)) ),
            ForAll( [x,y], Implies(p(x,y), r(x,y))),
        ]
# damo konjekturu
conjecture = ForAll([x,y], Implies(nm(x,y), r(x,y)))
solver.add(conjecture)

# check moze da primi pretpostavke (assumptions), tj nase aksiome
if solver.check(axioms) == sat:
    print(solver.model())
else:
    print("unsatisfiable")

# primetimo kakav ispis dobijamo. Mi ovde nismo nigde naveli sta je zapravo neka konkretna prava iz skupa P
# ono sto mi radimo je da samo proveravamo da li je skup uslova zadovoljiv