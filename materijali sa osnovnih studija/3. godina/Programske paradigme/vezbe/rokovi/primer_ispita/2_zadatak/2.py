import constraint

def cena(a,b,c,d,e,f):
    return a*30 + b*300 + c*50 + d*170 + e*400 + f*450 <= 1170

def kesice(a,b,c,d,e,f):
    return a + b + c + d + e + f <= 10

def mast(a,b,c,d,e,f):
    return a*30 + b*10 + c*150 + d*32 + e*3 + f*15 < 500

def secer(a,b,c,d,e,f):
    return a*5 + b*30 + c*2 + d*15 + e*45 + f*68 <= 150

problem = constraint.Problem()

problem.addVariable('brasno', range(0,11))
problem.addVariable('plazma', [0,1,2,3])
problem.addVariable('jaja', range(0,8))
problem.addVariable('mleko', range(0,6))
problem.addVariable('visnja', [0,1,2])
problem.addVariable('nutela', [0,1,2])

problem.addConstraint(cena, ['brasno', 'plazma', 'jaja', 'mleko', 'visnja', 'nutela'])
problem.addConstraint(kesice, ['brasno', 'plazma', 'jaja', 'mleko', 'visnja', 'nutela'])
problem.addConstraint(mast, ['brasno', 'plazma', 'jaja', 'mleko', 'visnja', 'nutela'])
problem.addConstraint(secer, ['brasno', 'plazma', 'jaja', 'mleko', 'visnja', 'nutela'])

resenja = problem.getSolutions()

maxProtein = 0

for r in resenja:
    novProtein = r['brasno']*20 + r['plazma']*15 + r['jaja']*70 + r['mleko']*40 + r['visnja']*23 + r['nutela']*7
    if novProtein > maxProtein:
        maxProtein = novProtein

print(maxProtein)
    