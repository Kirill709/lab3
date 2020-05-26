import numpy as np
import matplotlib.pyplot as plt
fig2=plt.figure()

ax2=plt.subplot('151')
data1 = np.loadtxt("Lagrange_Data.txt")
data2 = np.loadtxt("Nodes1.txt")
ax2.plot(data2[:,0],data2[:,1],'ro')
ax2.plot(data1[:,0],data1[:,1])

ax2=plt.subplot('152')
data1 = np.loadtxt("FirstNewton_Data.txt")
data2 = np.loadtxt("Nodes2.txt")
ax2.plot(data2[:,0],data2[:,1],'ro')
ax2.plot(data1[:,0],data1[:,1])

ax2=plt.subplot('153')
data1 = np.loadtxt("SecondNewton_Data.txt")
data2 = np.loadtxt("Nodes3.txt")
ax2.plot(data2[:,0],data2[:,1],'ro')
ax2.plot(data1[:,0],data1[:,1])

ax2=plt.subplot('144')
data1 = np.loadtxt("Steppolinom.txt")
data2 = np.loadtxt("Nodes4.txt")
ax2.plot(data2[:,0],data2[:,1],'ro')
ax2.plot(data1[:,0],data1[:,1])