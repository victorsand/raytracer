#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "MathEngine.h"

class Ray;
class IntersectionInfo;

class Triangle : public Shape {
public:
    Triangle(Point3f _v1, Point3f _v2, Point3f _v3);
    virtual IntersectionInfo rayIntersect(Ray _ray);
    Point3f v1() const { return v1_; }
    Point3f v2() const { return v2_; }
    Point3f v3() const { return v3_; }
    Vector3f normal() const { return normal_; }
private:
    Triangle();
    Triangle(const Triangle&);
    Point3f v1_;
    Point3f v2_;
    Point3f v3_;
    Vector3f normal_;
};

#endif