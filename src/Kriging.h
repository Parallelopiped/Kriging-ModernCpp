//
// Created by NaturalVStudio on 2022/6/25.
//

#ifndef KRIGING_MODERNCPP_KRIGING_H
#define KRIGING_MODERNCPP_KRIGING_H

#include "PointCloud.h"

class Kriging {
public:
    static std::shared_ptr<PointCloud> interpolation(const std::shared_ptr<PointCloud>& p_PC_input,
                                                     double step_x,
                                                     double step_y);

};


#endif //KRIGING_MODERNCPP_KRIGING_H
