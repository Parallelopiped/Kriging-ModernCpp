import numpy as np
import matplotlib.pyplot as plt

#plt.rcParams ['figure.dpi'] = 120

data_input = np.genfromtxt("../data/rectified2.txt", dtype=float)
data_output = np.genfromtxt("../data/KrigingOut2.txt", dtype=float)

# data_input = [np.array(i) for i in data_input]
data_input = data_input.T
data_output = data_output.T

ax = plt.subplot(projection = '3d')
ax.set_title('Fitted PointCloud')
ax.scatter(data_input[0], data_input[1], data_input[2], c='r')
ax.scatter(data_output[0], data_output[1], data_output[2], c='g', s=1)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
#ax.set_zlim(9, 15)
plt.show()
