//
// Created by NaturalVStudio on 2022/6/25.
//

//#define DEBUG

#include <iostream>
#include "PointCloud.h"

PointCloud::PointCloud() {
    p_cloud = std::make_shared<std::set<Vector3>>();
}

PointCloud::PointCloud(const std::shared_ptr<std::string> &p_inputPath): PointCloud() {
    std::ifstream file;
    file.open(*p_inputPath);

    int linesCnt = std::count(std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>(), '\n');
    if (linesCnt == 0){
        puts("No linesCnt!");
    }
    file.clear();
    file.seekg(0);
    size_t p = 0;
    std::string line;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        double x, y, z;
        if (!(iss >> x >> y >> z)){
            puts("FILE IS BAD FORMATTED!");
        }

        p_cloud->insert(Vector3(x, y, z));
    }
    file.close();

#ifdef DEBUG
    std::cout << p_cloud->size() << std::endl;
    for (auto v : *p_cloud) {
        std::cout << v.toString();
    }
#endif
}

size_t PointCloud::getSize() {
    return this->p_cloud->size();
}
