#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "MathEngine.h"

class Ray;
class IntersectionInfo;


class Sphere : public Shape {
public:
    Sphere(Point3f _center, float _radius);
    virtual IntersectionInfo rayIntersect(Ray _ray);
    Point3f center() { return center_; }
    float radius() { return radius_; }
private:
    Sphere();
    Sphere(const Sphere&);
    Point3f center_;
    float radius_;
};

#endif