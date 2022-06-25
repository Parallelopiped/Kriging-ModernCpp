//
// Created by NaturalVStudio on 2022/6/25.
//

#ifndef KRIGING_MODERNCPP_VECTOR3_HPP
#define KRIGING_MODERNCPP_VECTOR3_HPP

#include <cstdlib>
#include <cmath>
#include <cassert>
#include <string>
#include <sstream>
#include <memory>

using std::endl;

class Vector3{
public:
    double x;
    double y;
    double z;

    Vector3(): x(0), y(0), z(0) {};
    Vector3(double _x, double _y, double _z): x(_x), y(_y), z(_z) {};
    explicit Vector3(Vector3* v): Vector3(v->x, v->y, v->z) {};

    inline Vector3 operator + (Vector3 other) const;
    inline Vector3 operator - () const;
    inline Vector3 operator - (Vector3 other) const;
    inline Vector3 operator * (double scalar) const;
    inline double operator * (Vector3 other) const;

//    bool operator == (const Vector3& vector3) const{
//        return x == vector3.x && y == vector3.y;
//    }
    bool operator < (const Vector3& vector3) const{
        if (x == vector3.x && y == vector3.y) return false;
        return x == vector3.x ? y < vector3.y : x < vector3.x;
    }

    inline static double distance(Vector3 a, Vector3 b);

    [[nodiscard]] inline std::string toString() const;
};

Vector3 Vector3::operator + (Vector3 other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vector3 Vector3::operator-(Vector3 other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vector3 Vector3::operator - () const {
    return {-x ,-y, -z};
}

double Vector3::operator*(Vector3 other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::operator*(double scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

std::string Vector3::toString() const {
    std::stringstream s;
    s.precision(4); //manages decimal precision of floating point operations
    s << "(" << x << "," << y << "," << z << ")" << endl;
    return s.str();
}

double Vector3::distance(const Vector3 a, const Vector3 b) {
    auto p = std::make_shared<Vector3>(a - b);
    auto t = p->x * p->x + p->y * p->y;
    return sqrt(t);
}

#endif //KRIGING_MODERNCPP_VECTOR3_HPP
