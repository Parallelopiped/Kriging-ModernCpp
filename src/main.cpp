#include <memory>
#include "Vector3.hpp"
#include "Utils.hpp"
#include "Matrix.hpp"
#include "PointCloud.h"
#include "Kriging.h"
#include "Variogram.hpp"

using std::cout;

//void writeToFile(auto p_PC, auto filename);

int main() {
    /// customized parameter
    VariogramModel variogramModel{0.01, 5.5, 10.1, SPHERICAL};
    double step_x = 1;
    double step_y = 1;
    ///

    auto p_inputPath = std::make_shared<std::string>
            (R"(../data/input2.txt)");
    auto p_pointCloud_input = std::make_shared<PointCloud>(p_inputPath);
    auto p_pointCloud_output = Kriging::interpolation(p_pointCloud_input, step_x, step_y, variogramModel);

    std::stringstream outStream;
    outStream << "../data/KrigingOut.txt";
    FileOption::writeToFile(p_pointCloud_output, outStream.str());
    return 0;
}
