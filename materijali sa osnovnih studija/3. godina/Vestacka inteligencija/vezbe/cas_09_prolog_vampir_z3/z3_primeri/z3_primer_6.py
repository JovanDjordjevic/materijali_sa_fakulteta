from z3 import *

# Svaka dva brata imaju zajedničkog roditelja.
# Roditelj je stariji od deteta.
# Postoje braća.
# Ni jedna osoba nije starija od druge.             # conjecture

B = BoolSort()
O = DeclareSort("Osoba")

b = Function('braca', O, O, B)    # braca:  (osoba, osoba) -> bool
r = Function('roditelj', O, O, B)
s = Function('stariji', O, O, B)

x, y, z = Consts('x, y z', O)

axioms = [
            ForAll( [x,y], Exists([z], Implies(b(x,y), And(r(z,x), r(z,y))) ) ),
            ForAll( [x,y], Implies(r(x,y), s(x,y)) ),
            Exists( [x,y], b(x,y))
         ]

conjecture = ForAll( [x,y], Not(s(x,y)) )

solver = Solver()
solver.add(conjecture)

if solver.check(axioms) == sat:
    print(solver.model())
else:
    print("unsatisfiable")