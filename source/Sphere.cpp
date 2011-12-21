#include "Sphere.h"
#include "Ray.h"
#include "IntersectionInfo.h"
#include <iostream>

Sphere::Sphere(Point3f _center, float _radius)
    : center_(_center), radius_(_radius) {}

IntersectionInfo Sphere::rayIntersect(Ray _ray) {
    Point3f e = _ray.e();
    Point3f c = center_;
    Vector3f d = _ray.d();
    float discriminant = dot(d,(e-c))*dot(d,(e-c))- 
        dot(d,d)*(dot((e-c),(e-c))-radius_*radius_);
    if (discriminant < 0.0) {
        return IntersectionInfo(0.0, 
                                Point3f(),
                                Vector3f(),
                                IntersectionInfo::miss());
    } else {
        float t1 = (dot(d*-1.0,(e-c))+sqrt(discriminant))/dot(d,d);
        float t2 = (dot(d*-1.0,(e-c))-sqrt(discriminant))/dot(d,d);
        float t;
        if (t1 < t2) {
            t = t1;
        } else {
            t = t2;
        }
        if (t < _ray.tMin() || t > _ray.tMax()) {
            return IntersectionInfo(0.0, 
                                    Point3f(),
                                    Vector3f(),
                                    IntersectionInfo::miss());
        }
        Point3f p = e + d*t;
        Vector3f n = 2.0*(p-c);
        n.normalize();       
        return IntersectionInfo(t, p, n, IntersectionInfo::hit());
    }
}



