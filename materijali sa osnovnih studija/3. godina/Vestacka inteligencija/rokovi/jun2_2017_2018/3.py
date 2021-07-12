# resenje u z3 i minisat 

from z3 import *

# true jagoda, false visnja

# z3 za kvadrat
gl, gd, dl, dd = Bools('gl gd dl dd')

s = Solver()
s.add(gl==True)
s.add( Not(gl == gd) )
s.add( Not(gl == dl) )
s.add( Not(gd == dd) ) 
s.add( Not(dl == dd) )

print("KVADRAT:")
if s.check() == sat:
    print('satisfiable')
    print(s.model())
else:
    print('unsatisfiable')

# z3 za trougao
l, m, r = Bools('l m r')
s = Solver()
s.add( Not(l==m) )
s.add( Not(m==r) )
s.add( Not(r==l) )

print("TROUGAO:")
if s.check() == sat:
    print('satisfiable')
    print(s.model())
else:
    print('unsatisfiable')


# minisat za kvadrat:
# (gl) & ~(gl & gd) & ~(gl & dl) & ~(gd & dd) & ~(dl & dd)    
#  <=>    (gl) & (~gl | ~gd) & (~gl | ~dl) & (~gd | ~dd) & (~dl | ~dd) 
# u dimacs formatu:   (neka gl=1, gd=2, dl=3, dd=4)
# p cnf  4 5
# 1 0
# -1 -2 0
# -1 -3 0
# -2 -4 0
# -3 -4 0
