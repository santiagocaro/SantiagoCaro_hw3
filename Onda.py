import numpy as np
import matplotlib.pyplot as plt 
from matplotlib import animation

t1=60.0
t2=30.0
c=1
L=30.0
puntos=300
present=np.zeros((puntos,puntos))
present[(puntos/3),(puntos/2)]=-0.5
future=np.zeros((puntos,puntos))
grillas=[]
#print grillas

dx2=present.copy()
dy2=present.copy()

delta=L/puntos
dt=((0.5*(delta**2))/c**2)**(0.5)
pasos=int(t1/dt)
#pasos2=int(t2/dt)
r=((c**2)*(dt**2))/(2*(delta**2))

mascara=np.ones((puntos,puntos)) 
for j in range(puntos):
        if(j<145 or j>155):
                mascara[(200),j]=0.0
#print mascara[200,:] 

for i in range(1,puntos-1):
		for j in range(1,puntos-1):
                        future[i,j]=r*(present[i,j+1]+present[i,j-1]+present[i+1,j]+present[i-1,j]-4*present[i,j])+present[i,j]

past=present.copy()
present=future.copy()
present=present*mascara
#print future

for n in  range(pasos):
        for i in range(1,puntos-1):
                for j in range(1,puntos-1):
                        future[i,j]=r*2*(present[i,j+1]+present[i,j-1]+present[i+1,j]+present[i-1,j]-4*present[i,j])+2*present[i,j]-past[i,j]
        grillas.append(future)  
        past= present.copy()              
        present=future.copy()
        present=present*mascara                            

plt.imshow(grillas[-1])
plt.savefig("60Resultados_hw3.png")
plt.close()

plt.imshow(grillas[pasos/2])
plt.savefig("30Resultados_hw3.png")
plt.close()
'''
fig = plt.figure()
cubeta= plt.imshow(abs(grillas[0]), cmap='flag', extent=(30+delta, 30-delta, 30+delta, 30-delta))
def refresca(i):
        #datos=grillas[i]
        cubeta.set_array(grillas[i])
        return cubeta,


anim = animation.FuncAnimation(fig, refresca, np.arange(1,len(grillas)), interval=20, blit=False)
plt.show()
#anim.save('Onda.mp4', fps=10)
'''

