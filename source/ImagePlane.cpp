#include "ImagePlane.h"

ImagePlane::ImagePlane(Point3f _ll,
                       Point3f _ul,
                       Point3f _lr,
                       Point3f _ur,
                       Point3f _c) 
                       :
                       ll_(_ll),
                       ul_(_ul),
                       lr_(_lr),
                       ur_(_ur),
                       c_(_c) {}

ImagePlane::ImagePlane(const ImagePlane &_ip)
                       :   
                       ll_(_ip.ll()),
                       ul_(_ip.ul()),
                       lr_(_ip.lr()),
                       ur_(_ip.ur()),
                       c_(_ip.c()) {}

Point3f ImagePlane::imagePlanePoint(float _u, float _v) {

    
    float x = 
        (1.f-_u)*((1.f-_v)*ll_.x()+_v*ul_.x())+_u*((1.f-_v)*lr_.x()+_v*ur_.x());
    float y = 
        (1.f-_u)*((1.f-_v)*ll_.y()+_v*ul_.y())+_u*((1.f-_v)*lr_.y()+_v*ur_.y());
    float z = 
        (1.f-_u)*((1.f-_v)*ll_.z()+_v*ul_.z())+_u*((1.f-_v)*lr_.z()+_v*ur_.z());
       
    return Point3f(x,y,z);
}
   
void ImagePlane::pixelIs(int _pixelIndex, Color4f _color) {
    pixelArray_.at(_pixelIndex) = _color;
}

Color4f ImagePlane::pixel(int _pixelIndex) {
    return pixelArray_.at(_pixelIndex);
}

void ImagePlane::pixelArraySizeIs(int _size) {
    pixelArray_.resize(_size);
}