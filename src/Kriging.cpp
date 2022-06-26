//
// Created by NaturalVStudio on 2022/6/25.
//

#include "Kriging.h"

#include "Utils.hpp"
#include <iostream>

//#define DEBUG

std::shared_ptr<PointCloud> Kriging::interpolation(
        const std::shared_ptr<PointCloud>& p_PC_input,
        double step_x,
        double step_y,
        VariogramModel v) {
    initTime();
    size_t n = p_PC_input->p_cloud->size();
    std::cout << n << std::endl;
#ifdef DEBUG
    int cnt = 0;
    for (auto i : *p_PC_input->p_cloud) {
        std::cout << cnt++ << " " << i.toString();
    }
#endif

    auto p_PC_grid = std::make_shared<PointCloud>(); // grid point cloud
    double minX = 1000000000, maxX = -1000000000, minY = 1000000000, maxY = -1000000000;
    for (auto point : *p_PC_input->p_cloud) {
        if (point.x < minX) minX = point.x;
        if (point.x > maxX) maxX = point.x;
        if (point.y < minY) minY = point.y;
        if (point.y > maxY) maxY = point.y;
    }
    double width = maxX - minX;
    double height = maxY - minY;
    int sizeX = (int)(floor(width / step_x)) + 1;
    int sizeY = (int)(floor(height / step_y)) + 1;
    std::cout << "PointCloud dimensions in units: " << sizeX << " X " << sizeY << std::endl;
    for(int x = 0; x < sizeX; ++x)
    {
        double coordX = minX + x*step_x;
        for(int y = 0; y < sizeY; ++y)
        {
            double coordY = minY + y*step_y;
            p_PC_grid->p_cloud->insert(Vector3(coordX, coordY, 0));
        }
    }
    printTime("grid data prepared. finished at");
//    for (auto i : *p_PC_grid->p_cloud) {
//        std::cout << i.toString();
//    }
    auto p_M_V = std::make_shared<Matrix>
            (*Variogram::calcVariogram(p_PC_input, p_PC_input, v));
    printTime("Variogram of sampling data calculated. finished at");

    p_M_V->invert(); // invert
    printTime("Variogram matrix inverted. finished at");
#ifdef DEBUG
    p_M_V->I->print();
#endif
    for (auto itr = p_PC_grid->p_cloud->begin(); itr != p_PC_grid->p_cloud->end(); itr++) {
        auto p_M_D = Variogram::calcVariogram(std::make_shared<Vector3>(*itr), p_PC_input, v);
#ifdef DEBUG
        p_M_D->print();
#endif
        Matrix M_W = p_M_V->I->multiply(*p_M_D);
        int i = 0;
        for (auto val : *p_PC_input->p_cloud) {
            const_cast<Vector3*>(&(*itr))->z += M_W(i++, 0) * val.z;
        }
    }
    printTime("KRIGING Done. finished at");
    return p_PC_grid;
}
