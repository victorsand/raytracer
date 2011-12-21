#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

/*
Aggregates a Shape and a Material
*/

#include "Shape.h"
#include "Material.h"

class SceneObject {
public:
    SceneObject(Shape *_shape, Material _material);
    Shape* shape() { return shape_; }
    Material material() { return material_; }
private:
    SceneObject();
    SceneObject(const SceneObject&);
    Shape *shape_;
    Material material_;
};

#endif