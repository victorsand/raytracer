// Victor Sand
// victor.sand@gmail.com

#include "FocusPlane.h"
#include "Ray.h"

FocusPlane::FocusPlane(Point3f _p0, Vector3f _normal) 
    : p0_(_p0), normal_(_normal) {}

FocusPlane::FocusPlane(const FocusPlane& _f)
    : p0_(_f.p0()), normal_(_f.normal()) {}

IntersectionInfo FocusPlane::rayIntersect(Ray _r) {
    float t = dot(normal_,(p0_-_r.e()) / dot(normal_,_r.d()));
    return IntersectionInfo(t, _r.e()+t*_r.d(),normal_,IntersectionInfo::hit());
}