#include "Ray.h"

Ray::Ray(Point3f _start, Vector3f _direction, float _tMin, float _tMax) 
    : e_(_start), d_(_direction), tMin_(_tMin), tMax_(_tMax) {}

Ray::Ray(const Ray& _r)
    : e_(_r.e()), d_(_r.d()), tMin_(_r.tMin()), tMax_(_r.tMax()) {}

