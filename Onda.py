import numpy as np
import matplotlib.pyplot as plt 

L=30.0
puntos=10
grilla=np.zeros((puntos,puntos))
grilla[(puntos/3),(puntos/2)]=-0.5
dx2=grilla.copy()
dy2=grilla.copy()
#print grilla
delta=L/puntos
#print delta
for i in range(1,puntos-1):
	for j in range(1,puntos-1):
		dx2[i,j]=(grilla[i,j+1]-2*grilla[i,j]+grilla[i,j-1])/delta**2
		dy2[i,j]=(grilla[i+1,j]-2*grilla[i,j]+grilla[i-1,j])/delta**2
#print dx2

