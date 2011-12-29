#include "Material.h"

Material::Material() 
    : ambient_(Color3f(0.0, 1.0, 0.0)),
      diffuse_(Color3f(0.0, 1.0, 0.0)),
      specular_(Color3f(0.0, 0.0, 0.0)),
      mirror_(Color3f(0.0, 0.0, 0.0)),
      emittance_(Color3f(0.0, 0.0, 0.0)),
      shine_(0.0) {}

Material::Material(const Material &_m)
    : ambient_(_m.ambient()),
      diffuse_(_m.diffuse()),
      specular_(_m.specular()),
      mirror_(_m.mirror()),
      emittance_(_m.emittance()),
      shine_(_m.shine()) {}

Material::Material(Color3f _ambient,
                   Color3f _diffuse,
                   Color3f _specular,
                   Color3f _mirror,
                   Color3f _emittance,
                   float _shine)
                   :
                   ambient_(_ambient),
                   diffuse_(_diffuse),
                   specular_(_specular),
                   mirror_(_mirror),
                   emittance_(_emittance),
                   shine_(_shine) {}

bool Material::emitting() const {
    return (emittance_.r()>0.001||emittance_.g()>0.001||emittance_.b()>0.001);
}


     