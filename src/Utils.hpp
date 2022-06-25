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

class Surface{
public:
    std::shared_ptr<Vector3> S{}; //domain surface
    double K; //size of points

};



#endif //KRIGING_MODERNCPP_UTILS_HPP
