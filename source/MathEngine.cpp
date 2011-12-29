#include "MathEngine.h"
#include <math.h>

Point3f::Point3f() 
    : x_(0.0), y_(0.0), z_(0.0) {}

Point3f::Point3f(float _x, float _y, float _z) 
    : x_(_x), y_(_y), z_(_z) {}

Point3f::Point3f(const Point3f &_p) 
    : x_(_p.x()), y_(_p.y()), z_(_p.z()) {}

void Point3f::pointIs(float _x, float _y, float _z) {
    x_ = _x;
    y_ = _y;
    z_ = _z;
}

Vector3f operator-(const Point3f &_p1, const Point3f &_p2) {
    return Vector3f(_p1.x()-_p2.x(), _p1.y()-_p2.y(), _p1.z()-_p2.z());
}

Point3f operator+(const Point3f &_p, const Vector3f &_v) {
    return Point3f(_p.x()+_v.x(), _p.y()+_v.y(), _p.z()+_v.z());
}

Point3f operator-(const Point3f &_p, const Vector3f &_v) {
    return Point3f(_p.x()-_v.x(), _p.y()-_v.y(), _p.z()-_v.z());
}

Point2i::Point2i() 
    : x_(0), y_(0) {}

Point2i::Point2i(int _x, int _y) 
    : x_(_x), y_(_y) {}

Point2i::Point2i(const Point2i &_p) 
    : x_(_p.x()), y_(_p.y()) {}

Vector3f::Vector3f() 
    : x_(0.0), y_(0.0), z_(0.0) {}

Vector3f::Vector3f(float _x, float _y, float _z) 
    : x_(_x), y_(_y), z_(_z) {}

Vector3f::Vector3f(const Vector3f &_v) 
    : x_(_v.x()), y_(_v.y()), z_(_v.z()) {}

float Vector3f::magnitude() const {
    return sqrt(x_*x_+y_*y_+z_*z_);
}

void Vector3f::vectorIs(float _x, float _y, float _z) {
    x_ = _x;
    y_ = _y;
    z_ = _z;
}

Vector3f operator*(const Vector3f& _v, const float &_f) {
    return Vector3f(_v.x()*_f, _v.y()*_f, _v.z()*_f);
}

Vector3f operator*(const float &_f, const Vector3f& _v) {
    return _v*_f;
}

Vector3f operator/(const Vector3f& _v, const float &_f) {
     return Vector3f(_v.x()/_f, _v.y()/_f, _v.z()/_f);
}

void Vector3f::normalize() {
    float m = (*this).magnitude();
    x_ = x_ / m;
    y_ = y_ / m;
    z_ = z_ / m;
}

float dot(const Vector3f& _a, const Vector3f& _b) {
    return _a.x()*_b.x()+_a.y()*_b.y()+_a.z()*_b.z();
}

Vector3f cross(const Vector3f &_a, const Vector3f &_b) {
    return Vector3f(_a.y()*_b.z() - _a.z()*_b.y(),
                   _a.z()*_b.x() - _a.x()*_b.z(),
                   _a.x()*_b.y() - _a.y()*_b.x());
                   
}

Vector3f operator+(const Vector3f &_a, const Vector3f &_b) {
    return Vector3f(_a.x() + _b.x(),
                    _a.y() + _b.y(),
                    _a.z() + _b.z());
}
Vector3f operator-(const Vector3f &_a, const Vector3f &_b) {
    return Vector3f(_a.x() - _b.x(),
                    _a.y() - _b.y(),
                    _a.z() - _b.z());
}

Color3f::Color3f() 
    : r_(0.0), b_(0.0), g_(0.0) {}

Color3f::Color3f(float _r, float _g, float _b) 
    : r_(_r), g_(_g), b_(_b) {}

Color3f::Color3f(const Color3f& _c) 
    : r_(_c.r()), g_(_c.g()), b_(_c.b()) {}

void Color3f::operator+=(const Color3f& _c) {
    r_ += _c.r();
    g_ += _c.g();
    b_ += _c.b();
}

void Color3f::truncate() {
    if (r_ > 1.f) r_ = 1.f;
    if (g_ > 1.f) g_ = 1.f;
    if (b_ > 1.f) b_ = 1.f;
}

void Color3f::normalize() {
    float m = 0.f;
    if (r_ > m) m = r_;
    if (g_ > m) m = g_;
    if (b_ > m) m = b_;
    r_ /= m;
    g_ /= m;
    b_ /= m;
}

Color3f operator*(const Color3f& _c1, const Color3f& _c2) {
    return Color3f(_c1.r()*_c2.r(),
                   _c1.g()*_c2.g(),
                   _c1.b()*_c2.b());
}

Color3f operator+(const Color3f& _c1, const Color3f& _c2) {
    return Color3f(_c1.r()+_c2.r(),
                   _c1.g()+_c2.g(),
                   _c1.b()+_c2.b());
}

Color3f operator*(const Color3f& _c, float _f) {
    return Color3f(_c.r()*_f, _c.g()*_f, _c.b()*_f); 
}

Color3f operator*(float _f, const Color3f& _c) {
    return Color3f(_c.r()*_f, _c.g()*_f, _c.b()*_f); 
}




