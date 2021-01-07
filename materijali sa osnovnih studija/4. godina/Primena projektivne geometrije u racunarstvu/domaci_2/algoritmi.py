import numpy as np

#pravi matricu M = [ [alfa*A] [beta*B] [gama*C] ]
def napravi_matricu(A, B, C, D):
    M = np.array([ [ A[0], B[0], C[0] ],
                   [ A[1], B[1], C[1] ],
                   [ A[2], B[2], C[2] ] ])
    b = np.array([ D[0], D[1], D[2] ])
    rez = np.linalg.solve(M, b)         #resi sistem linearnih jednacina
    alfa = rez[0]
    beta = rez[1]
    gama = rez[2]
    return np.array([ [ alfa * A[0], beta * B[0], gama * C[0] ],
                      [ alfa * A[1], beta * B[1], gama * C[1] ],
                      [ alfa * A[2], beta * B[2], gama * C[2] ] ])

#[f] = [h] *[g]^-1
def naivni(A, B, C, D, Ap, Bp, Cp, Dp):
    #trazimo [g]
    g = napravi_matricu(A, B, C, D)
    g_inv = np.linalg.inv(g)
    #trazimo [h]
    h = napravi_matricu(Ap, Bp, Cp, Dp)
    #nadjemo [f] = [h] *[g]^-1
    f = np.dot(h, g_inv)
    f = np.round(f, 5)    #da svi elementi budu na npr 5 decimala
    return f

#matrice za svaku korespodenciju od kojih cemo napraviti matricu za SVD dekompoziciju
def napravi_2x9_matricu(A, Ap):
    matrica = np.array([ [0, 0, 0, -Ap[2]*A[0], -Ap[2]*A[1], -Ap[2]*A[2], Ap[1]*A[0], Ap[1]*A[1], Ap[1]*A[2]],
                         [Ap[2]*A[0], Ap[2]*A[1], Ap[2]*A[2], 0, 0, 0, -Ap[0]*A[0], -Ap[0]*A[1], -Ap[0]*A[2]] ])
    return matrica

def dlt(lista):
    M = napravi_2x9_matricu(lista[0][0], lista[0][1])
    for i in range(1, len(lista)):
        m = napravi_2x9_matricu(lista[i][0], lista[i][1])
        M = np.vstack((M, m))
    #print(M)
    #SVD: A = U * D * V^T, treba nam V_t i kada je transponujemo, poslednja kolona matrice V je trazeno P
    _, _, Vt = np.linalg.svd(M)
    V = np.transpose(Vt)
    P = V[:, -1]
    P = P.reshape(3, 3) #da bude 3x3 matrica
    P = np.round(P, 5)  #npr na 5 decimala
    return P

def normalizacija(A, B, C, D):
    A = (A[0]/A[2], A[1]/A[2], 1)
    B = (B[0]/B[2], B[1]/B[2], 1)
    C = (C[0]/C[2], C[1]/C[2], 1)
    D = (D[0]/D[2], D[1]/D[2], 1)
    #teziste
    T = ( (A[0] + B[0] + C[0] + D[0])/4 , (A[1] + B[1] + C[1] + D[1])/4, 1)   
    #matrica translacije 
    G = np.array([ [1, 0, -T[0]],
                   [0, 1, -T[1]],
                   [0, 0, 1] ])   
    An = G.dot(A)
    Bn = G.dot(B)
    Cn = G.dot(C)
    Dn = G.dot(D)
    coef = (np.sqrt(An[0]*An[0] + An[1]*An[1]) + np.sqrt(Bn[0]*Bn[0] + Bn[1]*Bn[1]) + 
            np.sqrt(Cn[0]*Cn[0] + Cn[1]*Cn[1]) + np.sqrt(Dn[0]*Dn[0] + Dn[1]*Dn[1]) )/4
    #matrica skaliranja
    S = np.array([ [np.sqrt(2)/coef, 0, 0],
                   [0, np.sqrt(2)/coef, 0],
                   [0, 0, 1] ])   
    #T = S*G matrica normalizacije
    T = S.dot(G)
    return (T, T.dot(A), T.dot(B), T.dot(C), T.dot(D))

#nakon sto normalizujemo pocetne tacke i njihove slike, nadjemo P = Tp^-1 * Pn * T    
def dlt_normalizovan(A, B, C, D, Ap, Bp, Cp, Dp):
    T, An, Bn, Cn, Dn = normalizacija(A, B, C, D)
    Tp, Apn, Bpn, Cpn, Dpn, = normalizacija(Ap, Bp, Cp, Dp)

    lista = [(An, Apn), (Bn, Bpn), (Cn, Cpn), (Dn, Dpn)]   #jer sam dlt pisao tako da kao argument uzme listu
    Pn = dlt(lista)
    
    Tp_inv = np.linalg.inv(Tp)
    P = np.dot(Tp_inv, np.dot(Pn, T) )
    P = np.round(P, 5)  #npr na 5 decimala
    return P

#main
#tacke iz vaseg test primera
A = (-3, 2, 1)
B = (-2, 5, 2)
C = (1, 0, 3)
D = (-7, 3, 1)
E = (2, 1, 2)
F = (-1, 2, 1)
G = (1, 1, 1)
#pocetna matrica 
P = np.array([ [0, 3, 5],
               [4, 0, 0],
               [-1, -1, 6]])
Ap = P.dot(A)
Bp = P.dot(B)
Cp = P.dot(C)
Dp = P.dot(D)
Ep = P.dot(E)
Fp = P.dot(F)
Gp = P.dot(G)

print("\nRezultat naivnog algoritma:")
f = naivni(A, B, C, D, Ap, Bp, Cp, Dp)
print(f)

lista = [(A, Ap), (B, Bp), (C, Cp), (D, Dp)]
print("\nRezultat DLT algoritma za 4 korespodencije:")
d = dlt(lista)
print( d )

print("\nMatrica iz naivnog algoritma i matrica iz DLT su iste do na konstantni faktor:")
print( f[0][1]/d[0][1] )

lista = [(A, Ap), (D, Dp), (B, Bp), (C, Cp)]
print("\nRezultat DLT algoritma za 4 korespodencije sa promenjenim redosledom tacaka:")
print( dlt(lista) )

lista = [(A, Ap), (B, Bp), (C, Cp), (D, Dp), (E, Ep), (F, Fp), (G, Gp)]
print("\nRezultat DLT algoritma za 7 korespodencija:")
print( dlt(lista) )

print("\nRezultat DLT algoritma sa normalizacijom za 4 korespodencije:")
dn = dlt_normalizovan(A, B, C, D, Ap, Bp, Cp, Dp)
print( dn )

print("\nMatrica iz naivnog algoritma i matrica iz DLT sa normalizacijom su iste do na konstantni faktor:")
print( f[0][1]/dn[0][1] )
print("\n")

#NOTE: zaokruzivao sam brojeve u dobijenim matricama na 5 decimala tako da ce mozda biti malih razlika u slikama ispod
print("Slika tacke A izracunata pomocu matrice date u test primeru")
print((Ap[0]/Ap[2], Ap[1]/Ap[2], 1))

print("\nSlika tacke A izracunata pomocu matrice dobijene DLT algoritmom")
tmp = d.dot(A)
print((tmp[0]/tmp[2], tmp[1]/tmp[2], 1))

print("\nSlika tacke A izracunata pomocu matrice dobijene DLT algoritmom sa normalizacijom")
t = dn.dot(A)
print((t[0]/t[2], t[1]/t[2], 1))

print("\n")