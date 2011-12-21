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
    AmbientLight(Color4f _color);
    Color4f color() const { return color_; }
private:
    AmbientLight();
        AmbientLight(const AmbientLight&);
    Color4f color_;
};

#endif