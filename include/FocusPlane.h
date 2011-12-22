#ifndef FOCUSPLANE_H
#define FOCUSPLANE_H

#include "MathEngine.h"
#include "IntersectionInfo.h"
#include <vector>
class Ray;

class FocusPlane {
public:
    FocusPlane();
    FocusPlane(const FocusPlane& _fp);
    FocusPlane(Point3f _p0, Vector3f _normal);
    IntersectionInfo rayIntersect(Ray _r);
    Point3f p0() const { return p0_; }
    Vector3f normal() const { return normal_; }
private:
    Point3f p0_;
    Vector3f normal_;

};

#endif