# i. ”Svi vole Jelenu.”
# ii. ”Svakog đaka voli Nikola ili Jovan.”
# iii. ”Nikola ili Jovan vole sve đake.”
# iv. ”Svi koji vole Teodoru nisu đaci.”
# v. ”Niko ne voli i Mariju i Nikolu.”

# v(x,y) - x voli y
# d(x) - x je djak
# je - jelena
# ni - Nikola
# jo - Jovan
# te - teodora
# ma - marija

# (Ax) (v(x, je))
# (Ax) (d(x) => (v(ni, x) | v(jo, x)))
# ((Ax) (d(x) => v(ni,x))) | ((Ax) (d(x) => v(jo,x)))
# (Ax) (v(x,te) => ~d(x))
# ~[ (Ex) (v(x, ma) & v(x, ni)) ]    (moze i ovako: (Ax)(~v(x, ma) | ~v(x, ni))   )


# b) ove godine radimo solverima:
from z3 import *

B = BoolSort()
O = DeclareSort('Osoba')

# visi
v = Function('v', O, O ,B)

x, y, z, n, j, m, t = Consts('x y z n j m t', O)

axioms = [
            v(n, j),
            v(j, m),
            v(m, t),
            ForAll([x,y,z], Implies( And(v(x,y), v(y,z)), v(x,z) ) )
         ]

conjecture = v(n, t)

solver = Solver()

if solver.check(axioms) == sat:
    print("satisfiable")
    #print(solver.model())
else:
    pritn('unsatisfiable')


# vampire resenje (neprovereno)
# fof(a1, axiom, v(n,j))
# fof(a2, axiom, v(j, m))
# fof(a3, axiom, v(m,t))
# fof(a4, axiom, ![x]:( ![y]:( ![z]:( (v(x,y) & v(y,z) => v(x,z)) ) ) ) )
# fof(c1, conjecture, v(n, t))
