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

class Color4f {
public:
    Color4f(float _r, float _g, float _b, float _a);
    Color4f(const Color4f& _Color4f);
    Color4f();
    float r() const { return r_; }
    float g() const { return g_; }
    float b() const { return b_; }
    float a() const { return a_; }
    void operator+=(const Color4f& _c);
    void truncate();
private:
    float r_;
    float g_;
    float b_;
    float a_;
};

Color4f operator*(const Color4f& _c1, const Color4f& _c2);
Color4f operator*(const Color4f& _c, float _f);
Color4f operator*(float _f, const Color4f& _c);

#endif


