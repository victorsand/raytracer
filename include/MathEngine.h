/*
Victor Sand 
victor.sand@gmail.com
*/

#ifndef MATHENGINE_H
#define MATHENGINE_H

#ifndef M_PI
#define M_PI 3.141592653589793238f
#endif

class Point3f;
class Vector3f;

class Point3f {
public:
    Point3f();
    Point3f(float _x, float _y, float _z);
    Point3f(const Point3f &_point);
    float x() const { return x_; }
    float y() const{ return y_; }
    float z() const{ return z_; }
    void pointIs(float _x, float _y, float _z);
private:
    float x_;
    float y_;
    float z_;
};

Vector3f operator-(const Point3f &_p1, const Point3f &_p2);
Point3f operator+(const Point3f &_p, const Vector3f &_v);
Point3f operator-(const Point3f &_p, const Vector3f &_v);

class Point2i {
public:
    Point2i();
    Point2i(int _x, int _y);
    Point2i(const Point2i &_point);
    int x() const { return x_; }
    int y() const { return y_; }
private:
    int x_;
    int y_;
};

class Vector3f {
public:
    Vector3f();
    Vector3f(float _x, float _y, float _z);
    Vector3f(const Vector3f& _vector);
    float x() const { return x_; }
    float y() const { return y_; }
    float z() const { return z_; }
    float magnitude() const;
    void normalize();
    void vectorIs(float _x, float _y, float _z);
    static Vector3f cross(Vector3f _a, Vector3f _b);
private:
    float x_;
    float y_;
    float z_;
};

float dot(const Vector3f& _a, const Vector3f& _b);
Vector3f operator+(const Vector3f &_a, const Vector3f &_b);
Vector3f operator-(const Vector3f &_a, const Vector3f &_b);
Vector3f cross(const Vector3f &_a, const Vector3f &_b);
Vector3f operator*(const Vector3f& _v, const float &_f);
Vector3f operator*(const float &_f, const Vector3f& _v);
Vector3f operator/(const Vector3f& _v, const float &_f);

class Color3f {
public:
    Color3f(float _r, float _g, float _b);
    Color3f(const Color3f& _Color3f);
    Color3f();
    float r() const { return r_; }
    float g() const { return g_; }
    float b() const { return b_; }
    void operator+=(const Color3f& _c);
    void truncate();
    void normalize();
private:
    float r_;
    float g_;
    float b_;
};

Color3f operator*(const Color3f& _c1, const Color3f& _c2);
Color3f operator*(const Color3f& _c, float _f);
Color3f operator*(float _f, const Color3f& _c);
Color3f operator+(const Color3f& _c1, const Color3f& _c2);

#endif


