#include <memory>
#include "Vector3.hpp"
#include "Utils.hpp"
#include "Matrix.hpp"
#include "Kriging.h"

int main() {
    /// customized parameter ↓↓↓
    ///
    // model of variogram estimation, para: {C0, CX, A, VAR}
    VariogramModel variogramModel{-3.1, 0.1, 20.1, CIRCULAR};

    // Geometric parameters of the silo
    DataRectifier dataRectifier{5.95, 16.86, 4.5};

    double step_x = 0.1; // x axis grid point density
    double step_y = 0.1; // y axis grid point density

    auto p_inputPath = std::make_shared<std::string>
            (R"(../data/input2.txt)"); // input path
    std::stringstream outStream;
    outStream << "../data/KrigingOut2.txt"; //output path
    ///
    /// customized parameter ↑↑↑

    auto p_pointCloud_input = std::make_shared<PointCloud>(p_inputPath);
    auto p_pointCloud_output = Kriging::interpolation(p_pointCloud_input,
                                                      step_x, step_y,
                                                      variogramModel,
                                                      dataRectifier);
    FileOption::writeToFile(p_pointCloud_output, outStream.str());

    std::cout << "---\nMaterial volume: " << dataRectifier.calcSilo(p_pointCloud_output) << std::endl;

    return 0;
}
