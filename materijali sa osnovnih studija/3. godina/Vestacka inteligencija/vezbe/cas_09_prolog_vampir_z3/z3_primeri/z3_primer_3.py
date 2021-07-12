from z3 import *

# primer kako mozemo definisati sopstvene prediakte i funkcije

# moramo da definisemo prvo nas novi Sort (vrstu) pomocu DeclareSort('ime') funkcije   (?)

# aok nam treba npr funkcija koja slika iz bool u int, treba da napravimo prvo ta dva domena
B = BoolSort()
Z = IntSort()

# i sad kad imamo domene mozemo napraviti funkciju
f = Function('f', B, Z)
g = Function('g', Z, B)

a = Bool('a')

solve( g(1+f(a)) )
