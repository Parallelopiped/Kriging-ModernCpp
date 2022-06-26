//
// Created by NaturalVStudio on 2022/6/25.
//

#ifndef KRIGING_MODERNCPP_POINTCLOUD_H
#define KRIGING_MODERNCPP_POINTCLOUD_H

#include <set>
#include <fstream>
#include <algorithm>

#include "Vector3.hpp"

class PointCloud {
public:
    std::shared_ptr<std::set<Vector3>> p_cloud;
    //int size;

    PointCloud();
    explicit PointCloud(const std::shared_ptr<std::string>& p_inputPath);

    size_t getSize();
    //static PointCloud loadPointCloud(const std::shared_ptr<std::string>& p_inputPath, int& lines);
};


#endif //KRIGING_MODERNCPP_POINTCLOUD_H
