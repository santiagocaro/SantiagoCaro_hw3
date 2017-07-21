import numpy as np
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt 

fig=plt.figure()
ax=fig.add_subplot(111,projection='3D')

X=np.random.rand(5)
Y=np.random.rand(5)
Z=np.random.rand(5)
print x

ax.scatter(X,Y,Z, c='r', marker='o')

ax.set_xlabel('Eje x')
ax.set_xlabel('Eje y')
ax.set_xlabel('Eje z')

plt.savefig("Resultados_hw3.pdf")

