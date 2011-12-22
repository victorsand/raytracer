#include "AreaLight.h"
#include <random>

AreaLight::AreaLight(Point3f _c, Vector3f _a, Vector3f _b, Color4f _color)
    : c_(_c), a_(_a), b_(_b), color_(_color) {}

std::vector<Vector3f> 
AreaLight::surfaceToLightDirection(Point3f _point, int _samples) const {
    std::vector<Vector3f> dirs;
    for (int i=0; i<_samples; ++i) {
        float r1 = (float)rand()/(float)RAND_MAX;
        float r2 = (float)rand()/(float)RAND_MAX;
        Point3f p = c_ + r1*a_ + r2*b_;
        dirs.push_back(p-_point);
    }
    return dirs;
}