#include "PointLight.h"

PointLight::PointLight(Point3f _position, Color4f _color) 
    : color_(_color), position_(_position) {}

Vector3f PointLight::surfaceToLightDirection(Point3f _surfacePoint) const {
    return position_ - _surfacePoint;
}