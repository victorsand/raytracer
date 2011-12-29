#include "PointLight.h"

PointLight::PointLight(Point3f _position, Color3f _color) 
    : color_(_color), position_(_position) {}

std::vector<Vector3f>
PointLight::surfaceToLightDirection(Point3f _point, int _samples) const {
    std::vector<Vector3f> dir;
    dir.push_back(position_ - _point);
    return dir;
}