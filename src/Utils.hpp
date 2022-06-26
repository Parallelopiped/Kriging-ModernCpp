//
// Created by NaturalVStudio on 2022/6/25.
//

#ifndef KRIGING_MODERNCPP_UTILS_HPP
#define KRIGING_MODERNCPP_UTILS_HPP

#include <iostream>

#include <algorithm>
#include <sstream>
#include <fstream>
#include <memory>
#include <ctime>

#include "PointCloud.h"

inline std::clock_t start;

inline void initTime()
{
    start = clock();
}

inline void printTime(const std::string& message)
{
    float lap = float(clock () - start) /  CLOCKS_PER_SEC;
    std::cout << message << ": " << lap << " Seconds" << endl;
}

struct FileOption{
    inline static void writeToFile(const std::shared_ptr<PointCloud>& p,
                                   const std::string& filename){
        std::ofstream o;
        o.open (filename);
        for (auto line : *p->p_cloud) {
            o << std::fixed << line.x << " " << line.y << " " << line.z << "\n";
        }
        o.close();
    }
};


#endif //KRIGING_MODERNCPP_UTILS_HPP
