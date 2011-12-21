#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
#include "MathEngine.h"

class PointLight : public Light {
public:
    PointLight(Point3f _position, Color4f _color);
    virtual Vector3f surfaceToLightDirection(Point3f _surfacePoint) const ;
    virtual Color4f color() const { return color_; }
    Point3f position() const { return position_; }
private:
    PointLight();
    PointLight(const PointLight&);
    Point3f position_;
    Color4f color_;
};

#endif