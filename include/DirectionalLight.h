#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"
#include "MathEngine.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(Vector3f _direction, Color4f _color);
    virtual Vector3f surfaceToLightDirection(Point3f _surfacePoint) const;
    virtual Color4f color() const { return color_; }
    Vector3f direction() const { return direction_; }
private:
    DirectionalLight();
    DirectionalLight(const DirectionalLight&);
    Vector3f direction_;
    Color4f color_;
};

#endif