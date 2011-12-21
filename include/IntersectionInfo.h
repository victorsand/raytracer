#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

/*
Class for storing Ray-Object intersection information. Stores a
true/false status for determining if the intersection is an intersection or not.
Stores the t value at which the intersection occured, the intersection point
and the intersection normal.
*/

#include "MathEngine.h"
#include "Material.h"

class IntersectionInfo {
public:
    enum HitTest {
        miss_,
        hit_
    };
    static HitTest hit() { return hit_; }
    static HitTest miss() { return miss_; }
    IntersectionInfo();
    IntersectionInfo(float _t, 
                     Point3f _point, 
                     Vector3f _normal,
                     HitTest _hitTest);
    IntersectionInfo(const IntersectionInfo&);
    float t() const { return t_; }
    Point3f point() const { return point_; }
    Vector3f normal() const { return normal_; }
    HitTest hitTest() const { return hitTest_; }
private:
    float t_;
    Point3f point_;
    Vector3f normal_;
    HitTest hitTest_;
};

#endif