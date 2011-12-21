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
