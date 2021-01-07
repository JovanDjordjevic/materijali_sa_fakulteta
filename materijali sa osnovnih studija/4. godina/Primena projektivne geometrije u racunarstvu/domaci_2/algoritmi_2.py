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
    #f = np.round(f, 5)    #da svi elementi budu na npr 5 decimala
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
    #P = np.round(P, 5)  #npr na 5 decimala
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
    #P = np.round(P, 5)  #npr na 5 decimala
    return P

def normalizacija_5(A, B, C, D, E):
    A = (A[0]/A[2], A[1]/A[2], 1)
    B = (B[0]/B[2], B[1]/B[2], 1)
    C = (C[0]/C[2], C[1]/C[2], 1)
    D = (D[0]/D[2], D[1]/D[2], 1)
    E = (E[0]/E[2], E[1]/E[2], 1)
    #teziste
    T = ( (A[0] + B[0] + C[0] + D[0] + E[0])/4 , (A[1] + B[1] + C[1] + D[1] + E[1])/4, 1)   
    #matrica translacije 
    G = np.array([ [1, 0, -T[0]],
                   [0, 1, -T[1]],
                   [0, 0, 1] ])   
    An = G.dot(A)
    Bn = G.dot(B)
    Cn = G.dot(C)
    Dn = G.dot(D)
    En = G.dot(E)
    coef = (np.sqrt(An[0]*An[0] + An[1]*An[1]) + np.sqrt(Bn[0]*Bn[0] + Bn[1]*Bn[1]) + 
            np.sqrt(Cn[0]*Cn[0] + Cn[1]*Cn[1]) + np.sqrt(Dn[0]*Dn[0] + Dn[1]*Dn[1]) +
            np.sqrt(En[0]*En[0] + En[1]*En[1]))/4
    #matrica skaliranja
    S = np.array([ [np.sqrt(2)/coef, 0, 0],
                   [0, np.sqrt(2)/coef, 0],
                   [0, 0, 1] ])   
    #T = S*G matrica normalizacije
    T = S.dot(G)
    return (T, T.dot(A), T.dot(B), T.dot(C), T.dot(D), T.dot(E))

#nakon sto normalizujemo pocetne tacke i njihove slike, nadjemo P = Tp^-1 * Pn * T    
def dlt_normalizovan_5(A, B, C, D, E, Ap, Bp, Cp, Dp, Ep):
    T, An, Bn, Cn, Dn, En = normalizacija_5(A, B, C, D, E)
    Tp, Apn, Bpn, Cpn, Dpn, Epn = normalizacija_5(Ap, Bp, Cp, Dp, Ep)

    lista = [(An, Apn), (Bn, Bpn), (Cn, Cpn), (Dn, Dpn), (En, Epn)]   #jer sam dlt pisao tako da kao argument uzme listu
    Pn = dlt(lista)
    
    Tp_inv = np.linalg.inv(Tp)
    P = np.dot(Tp_inv, np.dot(Pn, T) )
    #P = np.round(P, 5)  #npr na 5 decimala
    return P

#main
#tacke iz vaseg test primera
y1 = (2, 1, 1)
y2 = (1, 2, 1)
y3 = (3, 4, 1)
y4 = (-1, -3, 1)
y5 = (-2, 5, 1)
y1p = (0, 1, 1)
y2p = (5, 0, 1)
y3p = (2, -5, 1)
y4p = (-1, -1, 1)
y5p = (4, 1, 2)

yn1 = (0, -3, 1)
yn2 = (0, -1, 1)
yn3 = (4, -1, 1)
yn4 = (-7, -4, 1)
yn5 = (0, 5, 1)
yn1p = (3, -1, 1)
yn2p = (4, 4, 1)
yn3p = (9, 1, 1)
yn4p = (5, -2, 1)
yn5p = (7, 2, 2)

print("\nRezultat naivnog algoritma:")
f = naivni(y1, y2, y3, y4, y1p, y2p, y3p, y4p)
print(f / f[0][0])

lista = [(y1, y1p), (y2, y2p), (y3, y3p), (y4, y4p)]
print("\nRezultat DLT algoritma za 4 korespodencije:")
d = dlt(lista)
print( d / d[0][0] )

print("\nRezultat DLT algoritma sa normalizacijom za 4 korespodencije:")
dn = dlt_normalizovan(y1, y2, y3, y4, y1p, y2p, y3p, y4p)
print( dn / dn[0][0] )

lista = [(y1, y1p), (y2, y2p), (y3, y3p), (y4, y4p), (y5, y5p)]
print("\nRezultat DLT algoritma za 5 korespodencija:")
d = dlt(lista)
print( d / d[0][0] )

print("\nRezultat DLT algoritma sa normalizacijom za 5 korespodencija (za y1, y2...):")
dn = dlt_normalizovan_5(y1, y2, y3, y4, y5, y1p, y2p, y3p, y4p, y5p)
print( dn / dn[0][0] )

print("\nRezultat DLT algoritma sa normalizacijom za 5 korespodencija (za yn1, yn2...):")
dn = dlt_normalizovan_5(yn1, yn2, yn3, yn4, yn5, yn1p, yn2p, yn3p, yn4p, yn5p)
print( dn / dn[0][0] )

print("\n")

# print("\nMatrica iz naivnog algoritma i matrica iz DLT sa normalizacijom su iste do na konstantni faktor:")
# print( f[0][1]/dn[0][1] )
# print("\n")

# #NOTE: zaokruzivao sam brojeve u dobijenim matricama na 5 decimala tako da ce mozda biti malih razlika u slikama ispod
# print("Slika tacke A izracunata pomocu matrice date u test primeru")
# print((Ap[0]/Ap[2], Ap[1]/Ap[2], 1))

# print("\nSlika tacke A izracunata pomocu matrice dobijene DLT algoritmom")
# tmp = d.dot(A)
# print((tmp[0]/tmp[2], tmp[1]/tmp[2], 1))

# print("\nSlika tacke A izracunata pomocu matrice dobijene DLT algoritmom sa normalizacijom")
# t = dn.dot(A)
# print((t[0]/t[2], t[1]/t[2], 1))

# print("\n")