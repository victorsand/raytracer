#ifndef LIGHT_H
#define LIGHT_H

/* 
Virtual base class for lights (except ambient).
Has a method for returning the direction to the
light, given a surface point. 
*/

class Point3f;
class Vector3f;
class Color4f;

class Light {
public:
    Light() {}
    Light(const Light&) {}
    virtual Vector3f surfaceToLightDirection(Point3f _surfacePoint) const = 0;
    virtual Color4f color() const = 0;
};

#endif