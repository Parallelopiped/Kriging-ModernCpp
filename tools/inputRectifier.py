import numpy as np
import matplotlib.pyplot as plt


data_input = np.genfromtxt("src/input.txt", dtype=float)
data_output = np.genfromtxt("Kriging.txt", dtype=float)

# data_input = [np.array(i) for i in data_input]
data_input = data_input.T
data_output = data_output.T
# print(data_input[0])
# for i in range(data_input[0]):
#     x_now, y_now = data_input[0][i], data_input[1][i]
#     for j in range(data_input[0]):
#         x_t, y_t = data_input[0][j], data_input[1][j]
#         if x_now == x_t and y_now == y_t:
#

ax = plt.subplot(projection = '3d')
ax.set_title('3d_image_show')
ax.scatter(data_input[0], data_input[1], data_input[2], c='r')
ax.scatter(data_output[0], data_output[1], data_output[2], c='g', s=1)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_zlim(9, 15)

plt.show()
