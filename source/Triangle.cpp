#include "Triangle.h"
#include "IntersectionInfo.h"
#include "Ray.h"

Triangle::Triangle(Point3f _v1, Point3f _v2, Point3f _v3) 
    : v1_(_v1), v2_(_v2), v3_(_v3) {
        Vector3f vector1 = v2_ - v1_;
        Vector3f vector2 = v3_ - v2_;
        Vector3f normal = cross(vector1, vector2);
        normal.normalize();
        normal_ = normal;
}

IntersectionInfo Triangle::rayIntersect(Ray _ray) {
    float a = v1_.x() - v2_.x();
    float b = v1_.y() - v2_.y();
    float c = v1_.z() - v2_.z();
    float d = v1_.x() - v3_.x();
    float e = v1_.y() - v3_.y();
    float f = v1_.z() - v3_.z();
    float g = _ray.d().x();
    float h = _ray.d().y();
    float i = _ray.d().z();
    float j = v1_.x() - _ray.e().x();
    float k = v1_.y() - _ray.e().y();
    float l = v1_.z() - _ray.e().z();
    float M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
    float t = (-1.f)*(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
    if (t<_ray.tMin() || t>_ray.tMax()) {
        return IntersectionInfo(0.f,
                                Point3f(), 
                                Vector3f(), 
                                IntersectionInfo::miss());
    }
    float gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
    if (gamma < 0.f || gamma > 1.f) {
        return IntersectionInfo(0.f,
                                Point3f(), 
                                Vector3f(), 
                                IntersectionInfo::miss());
    }
    float beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
    if (beta < 0.f || beta > (1.f - gamma)) {
        return IntersectionInfo(0.f,
                                Point3f(), 
                                Vector3f(), 
                                IntersectionInfo::miss());
    }
    return IntersectionInfo(t,
                            Point3f(_ray.e()+_ray.d()*t),
                            normal_,
                            IntersectionInfo::hit());

}
