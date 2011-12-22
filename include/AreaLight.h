// Victor Sand
// victor.sand@gmail.com

#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "Light.h"
#include "MathEngine.h"

class AreaLight : public Light {
public:
    AreaLight(Point3f _c, Vector3f _a, Vector3f _b, Color4f _color);
    virtual std::vector<Vector3f>
        surfaceToLightDirection(Point3f _point,
                                int _samples = 1) const;
    virtual float maxT() const { return 1.f; }
    virtual Color4f color() const { return color_; }
private:
    AreaLight();
    AreaLight(const AreaLight&);
    Point3f c_;
    Vector3f a_;
    Vector3f b_;
    Color4f color_;
};

#endif