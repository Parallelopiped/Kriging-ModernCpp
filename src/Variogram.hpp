//
// Created by NaturalVStudio on 2022/6/26.
//

#ifndef KRIGING_MODERNCPP_VARIOGRAM_HPP
#define KRIGING_MODERNCPP_VARIOGRAM_HPP

#include <cstdlib>
#include <cmath>

#include "PointCloud.h"
#include "Matrix.hpp"

enum VariogramType : unsigned {
    SPHERICAL = 1,
    EXPONENTIAL,
    GAUSSIAN,
    WAVE,
    RATIONAL_Q,
    CIRCULAR
};

struct VariogramModel {
    double C0; //NUGGET
    double CX; //SILL (C0+C)
    double A;  //RANGE (Max distance to consider v(a)=SILL)
    int VAR;   //Type of variogram to use
};

class Variogram{
private:
    static double sphericalVariogram(double H, double C0, double CX, double A){
        return H > A ? CX : C0 + ((CX-C0) * ((3*H)/(2*A))-(H*H*H)/(2*A*A*A));
    }
    static double exponentialVariogram(double H, double C0, double CX, double A){
        return C0 + ((CX-C0) * (1-exp((-H/A))));
    }
    static double gaussianVariogram(double H, double C0, double CX, double A){
        double e = (H/A) * (H/A);
        return C0 + ((CX-C0) * (1-exp(-e)));
    }
    static double waveVariogram(double H, double C0, double CX, double A){
        double e = H / A;
        return C0 + ((CX-C0) * (1-(sin(e)/e)));
    }
    static double rationalQuadraticVariogram(double H, double C0, double CX, double A){
        double e = (H*H) / (A*A);
        return C0 + ((CX-C0) * (e/(1+e)));
    }
    static double circularVariogram(double H, double C0, double CX, double A){
        if(H > A){
            return CX;
        }
        else{
            double e = H / A;
            double p = 2 / M_PI;
            double r = sqrt(1-e*e);
            return C0 + ((CX-C0) * (1-p*acos(e)+p*e*r));
        }
    }

public:
    static auto calcVariogram(const std::shared_ptr<PointCloud>& p_PC_A,
                              const std::shared_ptr<PointCloud>& p_PC_B,
                              VariogramModel v){
        size_t m = p_PC_A->getSize(), n = p_PC_B->getSize();
        auto p_M_dist = std::make_shared<Matrix>(m, n);
        int i = 0;
        for (auto a : *p_PC_A->p_cloud) {
            int j = 0;
            for (auto b : *p_PC_B->p_cloud) {
                double dist = Vector3::distance(a, b);
                switch (v.VAR) {
                    case SPHERICAL:
                        p_M_dist->set(i, j, sphericalVariogram(dist, v.C0, v.CX, v.A)); break;
                    case EXPONENTIAL:
                        p_M_dist->set(i, j, exponentialVariogram(dist, v.C0, v.CX, v.A)); break;
                    case GAUSSIAN:
                        p_M_dist->set(i, j, gaussianVariogram(dist, v.C0, v.CX, v.A)); break;
                    case WAVE:
                        p_M_dist->set(i, j, waveVariogram(dist, v.C0, v.CX, v.A)); break;
                    case RATIONAL_Q:
                        p_M_dist->set(i, j, rationalQuadraticVariogram(dist, v.C0, v.CX, v.A)); break;
                    case CIRCULAR:
                        p_M_dist->set(i, j, circularVariogram(dist, v.C0, v.CX, v.A)); break;
                }
                j++;
            }
            i++;
        }
        return p_M_dist;
    }

    static auto calcVariogram(const std::shared_ptr<Vector3>& p_V_A,
                              const std::shared_ptr<PointCloud>& p_PC_B,
                              VariogramModel v){
        size_t n = p_PC_B->getSize();
        auto p_M_dist = std::make_shared<Matrix>(n, 1);
        int j = 0;
        for (auto b : *p_PC_B->p_cloud) {
            double dist = Vector3::distance(*p_V_A, b);
            switch (v.VAR) {
                case SPHERICAL:
                    p_M_dist->set(j, 0, sphericalVariogram(dist, v.C0, v.CX, v.A)); break;
                case EXPONENTIAL:
                    p_M_dist->set(j, 0, exponentialVariogram(dist, v.C0, v.CX, v.A)); break;
                case GAUSSIAN:
                    p_M_dist->set(j, 0, gaussianVariogram(dist, v.C0, v.CX, v.A)); break;
                case WAVE:
                    p_M_dist->set(j, 0, waveVariogram(dist, v.C0, v.CX, v.A)); break;
                case RATIONAL_Q:
                    p_M_dist->set(j, 0, rationalQuadraticVariogram(dist, v.C0, v.CX, v.A)); break;
                case CIRCULAR:
                    p_M_dist->set(j, 0, circularVariogram(dist, v.C0, v.CX, v.A)); break;
            }
            j++;
        }
        return p_M_dist;
    }
};


#endif //KRIGING_MODERNCPP_VARIOGRAM_HPP
