#ifndef CAMERA_H
#define CAMERA_H

/*
Represents virtual scene camera.
*/

#include "MathEngine.h"
#include "Ray.h"

class Camera {
public:
    Camera(Point3f _eye,
           Vector3f _up, 
           Point3f _lookAt,
           float _fovy, 
           float _aspect);
    Ray generateRay(Point3f _imagePlanePoint);
    Point3f eye() const { return eye_; }
private:
    Camera();
    Camera(const Camera&);
    Point3f eye_;
    Vector3f up_;
    Point3f lookAt_;
    float fovy_;
    float aspect_;
};

#endif