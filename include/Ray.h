#ifndef RAY_H
#define RAY_H

/* 

*/

#include "MathEngine.h"

class Ray {
public:
    Ray();
    Ray(const Ray&);
    Ray(Point3f _start, Vector3f _direction, float _tMin, float _tMax);
    Point3f e() const { return e_; }
    Vector3f d() const { return d_; }
    float tMin() const { return tMin_; }
    float tMax() const { return tMax_; }
private:
    Point3f e_;
    Vector3f d_;
    float tMin_;
    float tMax_;
};

#endif