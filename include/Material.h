#ifndef MATERIAL_H
#define MATERIAL_H

#include "MathEngine.h"

class Material {
public:
    Material();
    Material(const Material&);
    Material(Color4f _ambient,
             Color4f _diffuse,
             Color4f _specular,
             Color4f _mirror, 
             Color4f _emmitance,
             float _shine);
    Color4f ambient() const { return ambient_; }
    Color4f diffuse() const { return diffuse_; }
    Color4f specular() const { return specular_; }
    Color4f mirror() const { return mirror_; }
    Color4f emittance() const { return emittance_; }
    float shine() const { return shine_; }
private:
    Color4f ambient_;
    Color4f diffuse_;
    Color4f specular_;
    Color4f mirror_;
    Color4f emittance_;
    float shine_;
};

#endif