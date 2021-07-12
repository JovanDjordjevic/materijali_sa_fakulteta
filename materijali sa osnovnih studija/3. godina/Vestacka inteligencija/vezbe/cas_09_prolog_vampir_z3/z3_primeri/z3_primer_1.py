from z3 import *
# moze i samo  import z3   ali onda pre svih funkcija moramo z3.funkc...

# pocecemo od nekih jednostavnih primera iz iskazne logike:

# napisati uslov da je 4-bitni broj palindrom ali da nisu svi bitovi isti

# z3 u pozadini koristi SMT-LIB2 biblioteku koja ima vec neke ugradjene tipove koji se nazivaju Sorts
# to su Bool, Int, Real, BitVector, Array, Index, Eleme, Strin, Seq S... (nema ce trebati mozda prva 3)
# su ovde dovoljni boolovi pa mozemo sa ugradjenom funkcijom da napravimo promenljive tog tipa
A, B, C, D = Bools('A B C D')

# vraca jedno resenje
solve( A==D, B==C, Not(And(A==B, B==C, C==D)) )

#mozemo i na drugi nacin. Napravimo instancu resavaca
s = Solver()
# u njega dodamo klauzule
s.add( A==D, B==C, Not(And(A==B, B==C, C==D)) )
# pitamo da li je zadovoljivo:
if s.check() == sat:
    print(s.model())

# kada bismo zeleli da odstampamo sve modele koji zadovoljavaju nase uslove, to ovde nije bas pravolinijski
# treba da kada nadjemo jedno resenje, ubacimo njegovu negaciju u skup nasih klauzula i onda da trazimo opet resenje
# i tako u krug dokle god ih ima