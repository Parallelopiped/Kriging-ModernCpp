cmake_minimum_required(VERSION 3.10)
project(Kriging_ModernCpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Kriging_ModernCpp src/main.cpp src/Utils.hpp src/Vector3.hpp src/PointCloud.cpp src/PointCloud.h src/Kriging.cpp src/Kriging.h src/Matrix.hpp src/Variogram.hpp)
