/*
Victor Sand 
victor.sand@gmail.com

The Scene class ties everything together!
*/


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
class FocusPlane;

class Scene {
public:
    enum RenderMode {
        rayTracing_,
        pathTracing_,
        photonMapping_,
    };
    static RenderMode rayTracing() { return rayTracing_; }
    static RenderMode pathTracing() { return pathTracing_; }
    static RenderMode photonMapping() { return photonMapping_; }
    void renderModeIs(RenderMode _mode);
    RenderMode renderMode() { return renderMode_; }
    Scene(std::string _sceneFileName);
    void parse(); // parse input text file with scene info
    void render(); // write to imageplane's Color4f pixel array
    void writeToFile(); // copy the rendered pixel array to the output file
    int outputWidth() const { return outputWidth_; }
    int outputHeight() const { return outputWidth_; }
    int bounceDepth() const { return bounceDepth_; }
    float shadowBias() const { return shadowBias_; }
    void cleanUp();
private:
    Scene();
    Scene(const Scene&);
    Color4f traceRay(Ray _r, int _depth);
    Color4f tracePath(Ray _r, int _depth);
    Color4f phongShade(IntersectionInfo _ii, Material _m);
    IntersectionInfo findNearestIntersection(Ray _r, Material& _m);
    Vector3f hemisphereVector(Vector3f _v);
    std::string sceneFileName_;
    std::vector<SceneObject*> sceneObject_;
    std::vector<Light*> light_;
    AmbientLight *ambientLight_;
    ImagePlane* imagePlane_;
    FocusPlane* focusPlane_;
    Camera* camera_;
    Material currentMaterial_;
    int outputWidth_;
    int outputHeight_;
    std::string outputFileName_;
    int bounceDepth_;
    int superSamplingFactor_;
    int pathTracingSamples_;
    int samplesPerAreaLight_;
    float shadowBias_;
    float focalLength_; 
    float apertureSize_;
    int dofSamples_;
    RenderMode renderMode_;
};

#endif