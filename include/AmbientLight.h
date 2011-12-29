#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

/* 
Since ambient light behaves differently than point/directional light,
it has a class on its own. It also makes it easier to make sure there is
only one ambient light in a scene.
*/

#include "MathEngine.h"

class AmbientLight {
public:
    AmbientLight(Color3f _color);
    Color3f color() const { return color_; }
private:
    AmbientLight();
        AmbientLight(const AmbientLight&);
    Color3f color_;
};

#endif