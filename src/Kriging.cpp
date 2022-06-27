//
// Created by NaturalVStudio on 2022/6/25.
//

#include "Kriging.h"

#include <iostream>

//#define DEBUG

std::shared_ptr<PointCloud> Kriging::interpolation(
        const std::shared_ptr<PointCloud>& p_PC_input,
        double step_x,
        double step_y,
        VariogramModel& v,
        DataRectifier& dataRectifier) {
    initTime();

    //inputPoint crop
    dataRectifier.inputPointCut(p_PC_input);
    FileOption::writeToFile(p_PC_input, "../data/rectified1.txt");

    size_t n = p_PC_input->p_cloud->size();
    std::cout << n << std::endl;
#ifdef DEBUG
    int cnt = 0;
    for (auto i : *p_PC_input->p_cloud) {
        std::cout << cnt++ << " " << i.toString();
    }
#endif

    auto p_PC_grid = std::make_shared<PointCloud>(); // grid point cloud
    double minX = -dataRectifier.radius, maxX = dataRectifier.radius;
    double minY = -dataRectifier.radius, maxY = dataRectifier.radius;

    double width = maxX - minX;
    double height = maxY - minY;
    int sizeX = (int)(floor(width / step_x)) + 1;
    int sizeY = (int)(floor(height / step_y)) + 1;
    std::cout << "PointCloud dimensions in units: " << sizeX << " X " << sizeY << std::endl;
    for(int x = 0; x < sizeX; ++x){
        double coordX = minX + x*step_x;
        for(int y = 0; y < sizeY; ++y){
            double coordY = minY + y*step_y;
            Vector3 tmp_vec = Vector3(coordX, coordY, 0);
            if (! dataRectifier.gridPointCut(tmp_vec)) // Crop the points outside the circle
                p_PC_grid->p_cloud->insert(tmp_vec);
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
