#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <vector>
#include "Light.h"
#include "MathEngine.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(Vector3f _direction, Color4f _color);
    virtual std::vector<Vector3f> 
        surfaceToLightDirection(Point3f _surfacePoint,
                                int samples_ = 1) const;
    virtual Color4f color() const { return color_; }
    virtual float maxT() const { return std::numeric_limits<float>::max(); }
    Vector3f direction() const { return direction_; }
private:
    DirectionalLight();
    DirectionalLight(const DirectionalLight&);
    Vector3f direction_;
    Color4f color_;
};

#endif