#include <memory>
#include "Vector3.hpp"
#include "Utils.hpp"
#include "PointCloud.h"
#include "Kriging.h"

using std::cout;

int main() {
    ///
    double step_x = 1;
    double step_y = 1;

    ///
    size_t lines = 0;
    auto p_inputPath = std::make_shared<std::string>
            (R"(D:\CLionProjects233\Kriging_ModernC++\data\input2.txt)");
    auto p_pointCloud_input = std::make_shared<PointCloud>(p_inputPath);
    lines = p_pointCloud_input->getSize();
    cout << lines;
    auto p_pointCloud_output = Kriging::interpolation(p_pointCloud_input, step_x, step_y);

    return 0;
}
