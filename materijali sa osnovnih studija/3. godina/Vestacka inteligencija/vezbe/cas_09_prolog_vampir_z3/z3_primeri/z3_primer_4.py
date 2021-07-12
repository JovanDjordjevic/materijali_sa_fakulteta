from z3 import *

# zapisimo sad neki izraz iz logike prvog reda
# da bismo koristili kvantifikatore, imamo ugradjene funkcije
#   ForAll( [niz_promenljivih], formula )
#   Exists( [niz_promenljivih], formula )

x, y = Ints("x y")

# hocemo npr da zapisemo:  (y <= 0) => (x < y)

solve([ y == x + 1,  ForAll([y], Implies(y<0, x<y)) ])