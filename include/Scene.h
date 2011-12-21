#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "Material.h"
#include "AmbientLight.h"
#include "Ray.h"

class Light;
class Camera;
class ImagePlane;
class SceneObject;
class Output;
class Color4f;
class IntersectionInfo;

class Scene {
public:
    Scene(std::string _sceneFileName);
    void parse(); // parse input text file with scene info
    void render(); // write to imageplane's Color4f pixel array
    void writeToFile(); // copy the rendered pixel array to the output file
    int outputWidth() const { return outputWidth_; }
    int outputHeight() const { return outputWidth_; }
    int bounceDepth() const { return bounceDepth_; }
    float shadowBias() const { return shadowBias_; }
private:
    Scene();
    Scene(const Scene&);
    Color4f traceRay(Ray _r, int _depth);
    Color4f phongShade(IntersectionInfo _ii, Material _m);
    std::string sceneFileName_;
    std::vector<SceneObject*> sceneObject_;
    std::vector<Light*> light_;
    AmbientLight *ambientLight_;
    ImagePlane* imagePlane_;
    Camera* camera_;
     Material currentMaterial_;
    int outputWidth_;
    int outputHeight_;
    std::string outputFileName_;
    int bounceDepth_;
    int superSamplingFactor_;
    float shadowBias_;
};

#endif