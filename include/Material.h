#ifndef MATERIAL_H
#define MATERIAL_H

#include "MathEngine.h"

class Material {
public:
    Material();
    Material(const Material&);
    Material(Color3f _ambient,
             Color3f _diffuse,
             Color3f _specular,
             Color3f _mirror, 
             Color3f _emmitance,
             float _shine);
    Color3f ambient() const { return ambient_; }
    Color3f diffuse() const { return diffuse_; }
    Color3f specular() const { return specular_; }
    Color3f mirror() const { return mirror_; }
    Color3f emittance() const { return emittance_; }
    bool emitting() const;
    float shine() const { return shine_; }
private:
    Color3f ambient_;
    Color3f diffuse_;
    Color3f specular_;
    Color3f mirror_;
    Color3f emittance_;
    float shine_;
};

#endif