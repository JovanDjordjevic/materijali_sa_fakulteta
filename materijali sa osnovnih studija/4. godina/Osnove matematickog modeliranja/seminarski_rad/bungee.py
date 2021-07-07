import matplotlib.pyplot as plt
import numpy as np

m0 = 60
l0 = 30
d0 = 10
g = 9.81

# koeficijent elasticnosti
k = (m0 * g) / d0                                         # 58.86
d = (m0*g + np.sqrt( m0*m0*g*g + 2*k*m0*g*l0 )) / k       # l0 + d je max dubina za nas m0 = 60 i izracuant k

t1 = np.sqrt(2 * l0 / g)

a = np.sin(t1 * np.sqrt(k / m0))
b = np.cos(t1 * np.sqrt(k / m0))

c0 = d0 * a - np.sqrt(2 * g * l0 * m0 / k) * b
c1 = d0 * b + np.sqrt(2 * g * l0 * m0 / k) * a 

t2 = np.sqrt(m0 / k) * np.arctan(c0 / c1) + np.pi / np.sqrt(k / m0) - t1
#print(t2)

period = 2 * (t1 + t2)
print("Period: {}".format(period))      

# grafik 1
time = np.linspace(0, period, 10000)
current_x = l0
position = [current_x]
v0 =  np.sqrt(2 * g * l0)
firstIteration = True
tmap = 0
for t in time[1 : ]:
    if current_x > 0:
        if firstIteration == True:
            current_x = l0 - (g * t * t) / 2
        else:
            current_x = v0 * (t - tmap) - g * (t - tmap) * (t - tmap) / 2
    elif current_x < 0:
        firstIteration = False
        current_x = c0 * np.sin( t * np.sqrt(k / m0) ) + c1 * np.cos( t * np.sqrt(k / m0) ) - d0

    if position[-1] < 0:
        tmap = t
                    
    position.append(current_x)

plt.plot(time, position)
plt.xlabel("Time")
plt.ylabel("Position")
plt.axhline(-d0, color = "green")      # dubina kada bi bilo obeseno u stanju mirovanja
plt.axhline(-d, color = "red")         # maksimalna dubina koju dostigne
# plt.legend(["x(t)", "visina u stanju mirovanja", "maksimalna dostignuta dubina"])
plt.show()


# grafik 2
masses = [i for i in range(1, 100)]
depth = []

for m in masses:
    d = (m*g + np.sqrt( m*m*g*g + 2*k*m*g*l0 )) / k
    depth.append(l0 + d)

plt.plot(masses, depth)
plt.xlabel("Masses")
plt.ylabel("Depth (l + d)")
plt.show()
