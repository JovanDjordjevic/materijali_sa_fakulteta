# ove godine za ovo koristimo z3, vampir i prolog i slicno
# (a) Ko uči znaće.                     # axiom
# (b) Ko zna taj ima dobre ocene.       # axiom
# (c) Student uči.                      # axiom
# (d) Student ima dobre ocene           # conjecture

# z3 python resenje
from z3 import * 

B = BoolSort()
O = DeclareSort('Osoba')

u = Function('u', O, B)  # uci
z = Function('z', O, B)  # zna
do = Function('do', O, B) # ima dobre ocene

x, s  = Consts('x s', O)

axioms = [
            ForAll([x], Implies(u(x), z(x))),
            ForAll([x], Implies(z(x), do(x))),
            u(s),
         ]

conjecture = do(s)

solver = Solver()
solver.add(conjecture)

if solver.check(axioms) == sat:
    print('satisfiable:')
    print(solver.model())
else:
    print('unsatisfiable')


# vampir resenje (neprovereno)
# fof(a1, axiom, ![x]:(uci(x) => zna(x)))
# fof(a1, axiom, ![x]:(zna(x) => ima_dobre_ocene(x)))
# fof(a1, axiom, uci(student))
# fof(a1, conjecture, ima_dobre_ocene(student))

# prolog resenje
# uci(student).
# zna(X) :- uci(X).
# ima_dobre_ocene(X) :- zna(X).
# i onda u prolog okruzenju pozovemo: ima_dobre_ocene(student)