#ifndef FIELD_H
#define FIELD_H
#include "point.h"

class Field
{
    Point A, B, C, D;

public:
    Field() : A(0, 0), B(0, 0), C(0, 0), D(0, 0) {}
    Field(const Point &A, const Point &B, const Point &C, const Point &D) : A(A), B(B), C(C), D(D) {}
    Field(const Field &other) : A(other.A), B(other.B), C(other.C), D(other.D) {}
    Field(const Point &A, const Point &B, const Point &C, const Point &D, bool sizeCheck);

    void setAll(const Point &A, const Point &B, const Point &C, const Point &D, bool sizeCheck);

    float getLength(const Point A, const Point B) const;

    float getArea() const;

    bool isInside(const Point &P) const;
};

#endif