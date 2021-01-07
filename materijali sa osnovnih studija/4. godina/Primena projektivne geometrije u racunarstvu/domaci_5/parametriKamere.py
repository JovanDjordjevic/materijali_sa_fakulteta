import numpy as np

indeksiGdeSeMenjaZnak = []

def parametriKamere(T):
    M1 = T[:, [1, 2, 3]] #bez prve
    M2 = T[:, [0, 2, 3]] #bez druge
    M3 = T[:, [0, 1, 3]] #bez trece
    M4 = T[:, [0, 1, 2]] #bez cetvrte
    if np.linalg.det(M4) < 0:
        M4 = -M4
    C = np.array([np.linalg.det(M1), -np.linalg.det(M2), np.linalg.det(M3), -np.linalg.det(M4)])
    C = C / C[3]
    C = np.array([C[0], C[1], C[2]])

    Q, R = np.linalg.qr( np.linalg.inv(M4) )

    if R[0][0] < 0:
        indeksiGdeSeMenjaZnak.append(0)
        R[0, :] *= -1
        Q[:, 0] *= -1

    if R[1][1] < 0:
        indeksiGdeSeMenjaZnak.append(1)
        R[1, :] *= -1
        Q[:, 1] *= -1

    if R[2][2] < 0:
        indeksiGdeSeMenjaZnak.append(2)
        R[2, :] *= -1
        Q[:, 2] *= -1

    K = np.linalg.inv(R)
    K = K / K[2][2]
    A = np.transpose(Q)
    return K, A, C

#main
n = int(input("unesi indeks\n"))
n = n % 10
print("poslednja cifra indeksa: n =", n)
T = np.array([[5, -1-2*n, 3, 18-3*n], 
              [0, -1, 5, 21],
              [0, -1, 0, 1]])

K, A, C = parametriKamere(T)
print("K:\n", np.round(K, 2), "\nA:\n", np.round(A, 2), "\nC:\n", C)