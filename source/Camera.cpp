#include "Camera.h"
#include <limits>

Camera::Camera(Point3f _eye,
               Vector3f _up, 
               Point3f _lookAt,
               float _fovy, 
               float _aspect) 
               :
               eye_(_eye),
               up_(_up),
               lookAt_(_lookAt),
               fovy_(_fovy),
               aspect_(_aspect) 
               {}

Ray Camera::generateRay(Point3f _imagePlanePoint) {
    Vector3f d = _imagePlanePoint - eye_;
    Ray r(eye_, d, 1.0, std::numeric_limits<float>::max());
    return r;
}

std::vector<Ray> Camera::generateApertureRays(Point3f _origin,
                                              Point3f _target,
                                              float _apertureSize,
                                              int _samples) {
    std::vector<Ray> rays;
    // If samples = 1, don't jitter!
    if (_samples == 1) {
        rays.push_back(Ray(_origin, 
                           _target-_origin,
                           0.f, 
                           std::numeric_limits<float>::max()));
    } else {
        // ww along the original ray's direction
        Vector3f ww = _target-_origin;
        ww.normalize();
        ww = ww*_apertureSize;
        // vv in up direction
        Vector3f vv = up_;
        vv.normalize();
        vv = vv*_apertureSize;
        // uu perpendicular to ww and vv
        Vector3f uu = cross(ww,vv);
        uu.normalize();
        uu = uu*_apertureSize;

        // create the aperture
        Point3f a1 = _origin+0.5f*_apertureSize*vv+0.5f*_apertureSize*uu;
        Point3f a2 = _origin+0.5f*_apertureSize*vv-0.5f*_apertureSize*uu;
        Point3f a3 = a1 - _apertureSize*vv;
        Vector3f v0 = a2-a1;
        Vector3f v1 = a3-a1;
        for (int i=0; i<_samples; ++i) {
            float r1 = (float)rand()/(float)RAND_MAX;
            float r2 = (float)rand()/(float)RAND_MAX;
            Point3f rayOrigin = a1 + r1*v0 + r2*v1;
            rays.push_back(Ray(rayOrigin,
                               _target-rayOrigin,
                               0.f,
                               std::numeric_limits<float>::max()));
        }
    }
    return rays;
}

void Camera::wIs(Vector3f _w) { w_ = _w; }
void Camera::uIs(Vector3f _u) { u_ = _u; }
void Camera::vIs(Vector3f _v) { v_ = _v; }
