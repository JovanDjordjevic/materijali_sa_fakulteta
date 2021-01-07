#nema test primera za ovaj zadatak

import constraint

def tezina(a,b,c,d,e):
    return a*480 + b*355 + c*160 + d*30 + e*72 <= 20000

def zapremina(a,b,c,d,e):
    return a*6*11.5 + b*5.7*8.9 + c*2*2 + d*28.5*110 + 29*132 <= 50000 

def cena(a,b,c,d,e):
    return a*1000 + b*2500 + c*800 + d*7000 + e*10000 <= 17000

problem=constraint.Problem()

problem.addVariable('m84',range(0,5))
problem.addVariable('m75',range(0,8))
problem.addVariable('p98',range(0,11))
problem.addVariable('tma4',[0,1,2])
problem.addVariable('tmrp6',[0,1])

problem.addConstraint(tezina, ['m84', 'm75', 'p98', 'tma4', 'tmrp6'])
problem.addConstraint(zapremina, ['m84', 'm75', 'p98', 'tma4', 'tmrp6'])
problem.addConstraint(cena, ['m84', 'm75', 'p98', 'tma4', 'tmrp6'])

resenja = problem.getSolutions()
maxEnergija = 0
maxResenje = resenja[0]
for r in resenja:
    energija = r['m84']*5.6 + r['m75']*9.9 + r['p98']*2.7 + r['tma4']*30.5 + r['tmrp6']*45.5
    if energija > maxEnergija:
        maxEnergija = energija
        maxResenje = r

print(maxEnergija)
print(maxResenje)