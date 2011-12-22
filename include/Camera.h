#ifndef CAMERA_H
#define CAMERA_H

/*
Represents virtual scene camera.
*/

#include "MathEngine.h"
#include "Ray.h"
#include <vector>

class Camera {
public:
    Camera(Point3f _eye,
           Vector3f _up, 
           Point3f _lookAt,
           float _fovy, 
           float _aspect);
    Ray generateRay(Point3f _imagePlanePoint);
    std::vector<Ray> generateApertureRays(Point3f _origin,
                                          Point3f _target,
                                          float _apertureSize,
                                          int _samples);
    Point3f eye() const { return eye_; }
    Vector3f w() const { return w_; }
    Vector3f u() const { return u_; }
    Vector3f v() const { return v_; }
    void wIs(Vector3f _w);
    void uIs(Vector3f _u);
    void vIs(Vector3f _v);
private:
    Camera();
    Camera(const Camera&);
    Point3f eye_;
    Vector3f up_;
    Vector3f w_;
    Vector3f u_;
    Vector3f v_;
    Point3f lookAt_;
    float fovy_;
    float aspect_;
};

#endif