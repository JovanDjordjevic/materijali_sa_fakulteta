def vektorski_proizvod (X, Y):
    x1 = X[1] * Y[2] - X[2] * Y[1]
    x2 = (-1) * ( X[0] * Y[2] - X[2] * Y[0] )
    x3 = X[0] * Y[1] - X[1] * Y[0]
    return (x1, x2, x3) 

def nevidljivo(P1, P2, P3, P5, P6, P7, P8):

    #od afinih pravimo homogene koortinate tako sto dodajemo 1 kao trecu koordiantu
    P1_h = (P1[0], P1[1], 1)
    P2_h = (P2[0], P2[1], 1)
    P3_h = (P3[0], P3[1], 1)
    P5_h = (P5[0], P5[1], 1)
    P6_h = (P6[0], P6[1], 1)
    P7_h = (P7[0], P7[1], 1)
    P8_h = (P8[0], P8[1], 1)
    
    P5P6 = vektorski_proizvod(P6_h, P5_h)
    P7P8 = vektorski_proizvod(P7_h, P8_h)
    Y_inf = vektorski_proizvod(P5P6, P7P8)

    P6P7 = vektorski_proizvod(P6_h, P7_h)
    P5P8 = vektorski_proizvod(P5_h, P8_h)
    Z_inf = vektorski_proizvod(P6P7, P5P8)

    prava_P3_Y_inf = vektorski_proizvod(P3_h, Y_inf)
    prava_P1_Z_inf = vektorski_proizvod(P1_h, Z_inf)

    P4 = vektorski_proizvod(prava_P3_Y_inf, prava_P1_Z_inf)
    
    print("Afine koordinate tacke P4: {}, {}".format( round(P4[0] / P4[2]), round(P4[1] / P4[2])))

#main
#afine koordinate temena iz slike kutija.png
P1 = (710, 270)
P2 = (380, 610)
P3 = (134, 431)
#P4 ce biti izracunato
P5 = (743, 96)
P6 = (356, 368)
P7 = (63, 224)
P8 = (506, 55)

nevidljivo(P1, P2, P3, P5, P6, P7, P8)