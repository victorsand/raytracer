#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <vector>
#include "Light.h"
#include "MathEngine.h"

class PointLight : public Light {
public:
    PointLight(Point3f _position, Color4f _color);
   virtual std::vector<Vector3f> 
        surfaceToLightDirection(Point3f _surfacePoint,
                                int samples_ = 1) const;
    virtual Color4f color() const { return color_; }
    virtual float maxT() const { return 1.f; }
    Point3f position() const { return position_; }
private:
    PointLight();
    PointLight(const PointLight&);
    Point3f position_;
    Color4f color_;
};

#endif