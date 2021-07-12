from z3 import *

# problem 8 dama

# promenljive ce nam biti oblika:
# Q_i = j     -> u i-tom redu dama se nalazi u j-toj koloni

# 
#Q = [ Int('Q_%i' % (i+1)) for i in range(8)]
Q = [ Int(f'Q_{i}') for i in range(8)]

# svaka dama mora biti u koloni numerisanoj od 1 do 8
val_c = [ And( 1 <= Q[i], Q[i] <= 8 ) for i in range(8)]

# da su sve vrednosti razlicite
# imamo ugraddjenu funkciju Distinct 
col_c = [ Distinct(Q) ]

# pravilo za dijagonale
# ugradjena funkcija If( uslov, ako_je_uslov_tacan_vrati_ovo, ako_je_uslov_netacan_vrati_ovo )
diag_c = [ If(i == j, True, And(Q[i]-Q[j] != i-j, Q[i]-Q[j] != j-i))  for i in range(8) for j in range(8) ]

solve(val_c + col_c + diag_c)