import numpy as np

            
def Euler2A (phi, theta, ksi):
    Rz = np.array([ [np.cos(ksi), -np.sin(ksi), 0],
                    [np.sin(ksi), np.cos(ksi), 0],
                    [0, 0, 1] ])
    Ry = np.array([ [np.cos(theta), 0, np.sin(theta)],
                    [0, 1, 0],
                    [-np.sin(theta), 0, np.cos(theta)] ])
    Rx = np.array([ [1, 0, 0],
                    [0, np.cos(phi), -np.sin(phi)],
                    [0, np.sin(phi), np.cos(phi)] ])
    A = np.dot(Rz, np.dot(Ry, Rx))
    return A

def AxisAngle(A):
    #dodata provera
    #mora sa isclose, ne sme == zbog gresaka pri zaokruzivanju
    if  np.isclose(np.dot(A, A.T), np.identity(3)).all() or not np.isclose(1, np.linalg.det(A)):
        print("Matrica A nije matrica rotacije")
        exit()
    M = A - np.identity(3)
    s1 = np.array([ M[0][0], M[0][1], M[0][2] ])
    s2 = np.array([ M[1][0], M[1][1], M[1][2] ])
    p = np.cross(s1, s2)
    p_norm = np.sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2])
    p = p/p_norm
    u = np.array([0, 1, -p[1]/p[2]])
    u_norm = np.sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2])
    u = u/u_norm
    up = np.dot(A, u)
    up_norm = np.sqrt(up[0]*up[0] + up[1]*up[1] + up[2]*up[2])
    phi = np.arccos( np.dot(u,up)/(u_norm*up_norm) )
    mesoviti = np.dot(u, np.cross(up, p))
    if mesoviti < 0:
        return p, -phi
    return p, phi

def Rodrigez(p, phi):
    ppt = np.array([ [p[0]*p[0], p[0]*p[1], p[0]*p[2]],
                     [p[1]*p[0], p[1]*p[1], p[1]*p[2]],
                     [p[2]*p[0], p[2]*p[1], p[2]*p[2]] ])
    px = np.array([ [0, -p[2], p[1]],
                    [p[2], 0, -p[0]],
                    [-p[1], p[0], 0] ])
    return ppt + np.cos(phi)*(np.identity(3) - ppt) + np.sin(phi)*px

def A2Euler(A):
    #dodata provera
    if not np.isclose(np.dot(A, A.T), np.identity(3)).all() or not np.isclose(1, np.linalg.det(A)):
        print("Matrica A nije matrica rotacije")
        exit()
    if A[2][0] < 1:
        if A[2][0] > -1:
            ksi = np.arctan2(A[1][0], A[0][0])
            theta = np.arcsin(-A[2][0])
            phi = np.arctan2(A[2][1], A[2][2])
        else:
            ksi = np.arctan2(-A[0][1], A[1][1])
            theta = np.pi/2
            phi = 0
    else:
        ksi = np.arctan2(-A[0][1], A[1][1])
        theta = -np.pi/2
        phi = 0
    
    return phi, theta, ksi

def AxisAngle2Q(p, phi):
    w = np.cos(phi/2)
    p_norm = np.sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2])
    p = p/p_norm 
    x = np.sin(phi/2)*p[0]
    y = np.sin(phi/2)*p[1]
    z = np.sin(phi/2)*p[2]
    return x, y, z, w

def Q2AngleAxis(q):
    x = q[0]
    y = q[1]
    z = q[2]
    w = q[3]
    q_norm = x*x + y*y + z*z + w*w
    #dodata provera da li je kvaternion jedinicni
    if q_norm != 1:
        x = x/q_norm
        y = y/q_norm
        z = z/q_norm
        w = w/q_norm
    if w < 0:
        x = -x
        y = -y
        z = -z
        w = -w
    phi = 2*np.arccos(w)
    if abs(w) == 1:
        p = (1, 0, 0)
    else:
        p_norm = np.sqrt(x*x + y*y + z*z)
        p = (x/p_norm, y/p_norm, z/p_norm)
    return p, phi

#main
#moodle test primer
phi = -np.arctan(1/4)
theta = -np.arcsin(8/9)
ksi = np.arctan(4)
#moj test primer
# phi = -np.pi/6
# theta = np.pi/3
# ksi = -3*np.pi/4

print("Euler2A:")
A = Euler2A(phi, theta, ksi)
print(A)

print("\nAxisAngle:")
vect, angle = AxisAngle(A)
print (vect, ",", angle)

print("\nRodrigez:")
R = Rodrigez(vect, angle)
print(R)

print("\nA2Euler:")
phi1, theta1, ksi1 = A2Euler(R)
print(phi1, theta1, ksi1)

print("\nAxisAngle2Q:")
x, y, z, w = AxisAngle2Q(vect, angle)
q = (x, y, z, w)
print(q)

print("\nQ2AngleAxis:")
p, phi = Q2AngleAxis(q)
print(p, phi)