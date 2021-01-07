# Operatori operacija nad brojevima se ne razlikuju previse od C-ovskih
# Definisemo 2 promenljive, x je celobrojna, a y realna
x = 3
y = 4.2

# Stampamo tipove promenljivih
print( type(x) )
print( type(y) )

# Stampa na ekran zbir dve promenljive
print(x + y)

# Stampa na ekran vrednost y na x-ti stepen
print(y ** x)                                   #!!!!!!

# Ceo deo kolicnika
print(y // x)					#!!!!

# Realan kolicnik  realne i celobrojne promenljive
print(y / x)

# Ostatak pri deljenju
print(y % x)

# Eksplicitna promena tipa (konverzija)
# u int, odnosno, u float
print( int(y) )
print( float(x) )

# Podrska za kompleksne brojeve
z = complex(x, y)
# ili z = (3+4.2j)   //U PYTHONU JE j A NE i ZA KOPLEKSNE!!!!!!!!!

print(z)
print( type(z) )

# Sabiranje sa celobrojnom promenljivom
print(z + x)
# Kompleksnim brojem
print(z + complex(1,x))
print (z + 20j)

# Realan i imaginaran deo kompleksne promenljive z
print(z.real, z.imag)

# Prikazujemo normu komplesnog broja
print(abs(z))  # sqrt(z.real**2 + z.imag**2)
