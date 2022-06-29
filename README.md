## Kriging method by Modern C++

### Environment:
> CMake >= 3.10
> 
> GCC >= 9.2

### file structure:
+ `src` is the main implementation of algorithm
+ `tools` contains some independent code clips for special requirement, such as visualization and data formatting.

### Input:
+ text file organized by multi-lines of `x y z`
+ use (`x` and `y`) as keys, while `z` for the value

### Output:
+ some details from Kriging method and their time cost;
+ the pointcloud of output was also formatted as `x y z`;

### Branches:
`master` branch is the main frame of algorithm, while `iot_course_project` is a course project based on it, of which the goal is to solve such problem of a silo's capacity. They won't be merged. BTW, any fork or pr is recommended to be done with the master branch.
