#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3f _direction, Color4f _color) 
    : color_(_color), direction_(_direction) {}

Vector3f 
DirectionalLight::surfaceToLightDirection(Point3f _surfacePoint) const {
    return -1.f*direction_;
}