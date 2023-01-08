#ifndef VECTOR_H
#define VECTOR_H
#include "point.h"
#include "field.h"
class Vector
{
    float x, y;

public:
    Vector() : x(0), y(0) {}
    Vector(float x, float y) : x(x), y(y) {}
    Vector(const Point p1, const Point p2);
    Vector(Field f, Vector v1, Vector v2, Point intr);

    Vector sum(const Vector &other) const;
    Vector times_num(float num) const;

    bool is_colinear(const Vector &other) const;
    double length() const;
    double HeronFormula(const Vector &other) const;
    void setPoints(const Point p1, const Point p2);
    bool one_way(const Vector &other) const;

    float getX() const { return x; }
    float getY() const { return y; }

    void reverse();
    void half();

    friend class Line;
    friend std::ostream &operator<<(std::ostream &os, const Vector &c);
    friend std::istream &operator>>(std::istream &in, Vector &v);
};

inline std::ostream &operator<<(std::ostream &out, const Vector &v)
{
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

inline std::istream &operator>>(std::istream &in, Vector &v)
{
    in >> v.x;
    in >> v.y;
    return in;
}

#endif