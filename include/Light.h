#ifndef LIGHT_H
#define LIGHT_H

/* 
Virtual base class for lights (except ambient).
Has a method for returning the direction to the
light, given a surface point. The result is a vector
which for points and directional lights only contains
a single direction, and possibly contains more for 
area lights. The functions takes an argument for number of
samples to be generated. This argument can be ignored for
point and diretional lights.

The maximum t value for occluding rays are different
for different kinds of lights, the function maxT() takes
care of that issue.
*/

#include <vector>

class Point3f;
class Vector3f;
class Color3f;

class Light {
public:
    Light() {}
    Light(const Light&) {}
    virtual std::vector<Vector3f> 
        surfaceToLightDirection(Point3f _point, 
                                int _samples = 1) const = 0;
    virtual float maxT() const = 0;
    virtual Color3f color() const = 0;
};

#endif