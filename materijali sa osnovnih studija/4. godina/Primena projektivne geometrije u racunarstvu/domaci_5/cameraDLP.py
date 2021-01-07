import numpy as np
from parametriKamere import indeksiGdeSeMenjaZnak

def napravi2x12matricu(original, projekcija):
    M = np.array([[0, 0, 0, 0, -projekcija[2]*original[0], -projekcija[2]*original[1], 
                   -projekcija[2]*original[2], -projekcija[2]*original[3], projekcija[1]*original[0], 
                   projekcija[1]*original[1],  projekcija[1]*original[2], projekcija[1]*original[3]],  #kraj prvog reda
                  [projekcija[2]*original[0], projekcija[2]*original[1], 
                   projekcija[2]*original[2], projekcija[2]*original[3], 0, 0, 0, 0,
                   projekcija[0]*original[0], projekcija[0]*original[1], projekcija[0]*original[2], 
                   projekcija[0]*original[3]]]) #kraj drugog reda
    return M

def CameraDLP(originali, projekcije):
    C = napravi2x12matricu(originali[0], projekcije[0])
    for i in range(1, len(originali)):
        tmp = napravi2x12matricu(originali[i], projekcije[i])
        C = np.concatenate((C, tmp))
    
    _, _, V_t = np.linalg.svd(C)
    V = np.transpose(V_t)

    T = V[:, -1]
    T = T.reshape(3, 4)

    #print(indeksiGdeSeMenjaZnak)  #iz parametriKamere.py
    for i in indeksiGdeSeMenjaZnak: 
        T[2 - i, :] *= -1

    return T/T[0][0]

n = int(input("\ncameraDLP\nUnesi indeks\n"))
n = n % 10
print("Poslednja cifra indeksa: n =", n)

M1 = (460, 280, 250, 1)
M2 = (50, 380, 350, 1)
M3 = (470, 500, 100, 1)
M4 = (380, 630, 50*n, 1)
M5 = (30*n, 290, 0, 1)
M6 = (580, 0, 130, 1)
originali = [M1, M2, M3, M4, M5, M6]

M1p = (288, 251, 1)
M2p = (79, 510, 1)
M3p = (470, 440, 1)
M4p = (520, 590, 1)
M5p = (365, 388, 1)
M6p = (365, 20, 1)
projekcije = [M1p, M2p, M3p, M4p, M5p, M6p]

print("Dobijena matrica kamere:\n", CameraDLP(originali, projekcije))