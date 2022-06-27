//
// Created by NaturalVStudio on 2022/6/25.
//

#ifndef KRIGING_MODERNCPP_KRIGING_H
#define KRIGING_MODERNCPP_KRIGING_H

#include "PointCloud.h"
#include "Variogram.hpp"
#include "Utils.hpp"

#include <algorithm>

class Kriging {
public:
    static std::shared_ptr<PointCloud> interpolation(const std::shared_ptr<PointCloud>& p_PC_input,
                                                     double step_x,
                                                     double step_y,
                                                     VariogramModel& v,
                                                     DataRectifier& dataRectifier);

};


#endif //KRIGING_MODERNCPP_KRIGING_H
