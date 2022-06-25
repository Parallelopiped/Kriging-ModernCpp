cmake_minimum_required(VERSION 3.20)
project(Kriging_ModernCpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Kriging_ModernCpp src/main.cpp src/Utils.hpp src/Vector3.hpp src/PointCloud.cpp src/PointCloud.h src/Kriging.cpp src/Kriging.h)
