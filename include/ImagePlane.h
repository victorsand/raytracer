#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "MathEngine.h"
#include <vector>

class ImagePlane {
public:
    ImagePlane();
    ImagePlane(const ImagePlane& _ip);
    ImagePlane(Point3f _ll,
               Point3f _ul,
               Point3f _lr,
               Point3f _ur,
               Point3f _c);
    Point3f ll() const { return ll_; }
    Point3f ul() const { return ul_; }
    Point3f lr() const { return lr_; }
    Point3f ur() const { return ur_; }
    Point3f c() const { return c_; }
    Point3f imagePlanePoint(float _u, float _v);
    void pixelArraySizeIs(int _size);
    void pixelIs(int _pixelIndex, Color4f _color);
    Color4f pixel(int _pixelIndex);
private:
    Point3f ll_;
    Point3f ul_;
    Point3f lr_;
    Point3f ur_;
    Point3f c_;
    std::vector<Color4f> pixelArray_;
};

#endif