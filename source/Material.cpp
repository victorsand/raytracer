#include "Material.h"

Material::Material() 
    : ambient_(Color4f(0.0, 1.0, 0.0, 1.0)),
      diffuse_(Color4f(0.0, 1.0, 0.0, 1.0)),
      specular_(Color4f(0.0, 1.0, 0.0, 1.0)),
      mirror_(Color4f(0.0, 1.0, 0.0, 1.0)),
      shine_(0.0) {}

Material::Material(const Material &_m)
    : ambient_(_m.ambient()),
      diffuse_(_m.diffuse()),
      specular_(_m.specular()),
      mirror_(_m.mirror()),
      shine_(_m.shine()) {}

Material::Material(Color4f _ambient,
                   Color4f _diffuse,
                   Color4f _specular,
                   Color4f _mirror,
                   float _shine)
                   :
                   ambient_(_ambient),
                   diffuse_(_diffuse),
                   specular_(_specular),
                   mirror_(_mirror),
                   shine_(_shine) {}


     