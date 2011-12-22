#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3f _direction, Color4f _color) 
    : color_(_color), direction_(_direction) {}

std::vector<Vector3f> 
DirectionalLight::surfaceToLightDirection(Point3f _point, int _samples) const {
    std::vector<Vector3f> dir;
    dir.push_back(-1.f*direction_);
    return dir;
}