#ifndef SHAPE_H
#define SHAPE_H

/*
Virtual base class representing geometric primitives in the scene. Has a method
for producing intersection info using from a given ray. 
*/

class IntersectionInfo;
class Ray;

class Shape {
public:
    Shape() {}
    Shape(const Shape&) {}
    virtual IntersectionInfo rayIntersect(Ray _ray) = 0;
};

#endif