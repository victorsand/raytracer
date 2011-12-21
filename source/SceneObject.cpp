#include "SceneObject.h"
#include "Shape.h"
#include "Material.h"

SceneObject::SceneObject(Shape *_shape, Material _material)
    : shape_(_shape), material_(_material) {}