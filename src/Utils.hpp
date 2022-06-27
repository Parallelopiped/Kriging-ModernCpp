//
// Created by NaturalVStudio on 2022/6/25.
//

#ifndef KRIGING_MODERNCPP_UTILS_HPP
#define KRIGING_MODERNCPP_UTILS_HPP

#define _USE_MATH_DEFINES

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <memory>
#include <ctime>

#include "PointCloud.h"

class DataRectifier{
public:
    double radius{};
    double cylinderHight{};
    double coneHight{};

protected:
    inline double f_cone(double& x, double& y) const{
        double k_cone =  this->coneHight / this->radius;
        double r_xy = sqrt(x*x + y*y);
        return k_cone * r_xy;
    }
    double area;

public:
    inline DataRectifier(double _r, double _cy, double _co): radius(_r), cylinderHight(_cy), coneHight(_co){
        this->area = radius * radius * M_PI;
    }
    inline bool gridPointCut(Vector3& vec) const{
        if (vec.x * vec.x + vec.y * vec.y >= radius * radius) return true;
        return false;
    }

    inline void inputPointCut(const std::shared_ptr<PointCloud>& p_PC_input) const{
        double avg = 0, edge_cnt = 0;
        for (auto point : *p_PC_input->p_cloud) {
            if (sqrt(point.x * point.x + point.y * point.y) >= this->radius * 0.75){
                avg += point.z;
                edge_cnt++;
            }
        }
        avg = avg / edge_cnt;
        std::cout << avg << std::endl;
        for (auto point : *p_PC_input->p_cloud) {
            if (sqrt(point.x * point.x + point.y * point.y) > this->radius * 0.9
                && point.z >= avg*0.95)
                p_PC_input->p_cloud->erase(point);
        }
    }

    [[nodiscard]] inline double calcSilo(const std::shared_ptr<PointCloud>& p_PC) const{
        size_t cnt_point = p_PC->getSize();
        double d_area = this->area / cnt_point;
        double sum_volume = 0;
        //int i = 0;
        for (auto point : *p_PC->p_cloud) {
            sum_volume += d_area * (point.z - f_cone(point.x, point.y));
            //if (i % 100 == 0) printf("sum_volume %d %lf\n", i, sum_volume);
            //i++;
        }
        return sum_volume;
    }
};


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
