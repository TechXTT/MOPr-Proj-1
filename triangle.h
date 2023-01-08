#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "point.h"

class Triangle
{
    Point A, B, C;

public:
    Triangle() : A(0, 0), B(0, 0), C(0, 0) {}
    Triangle(const Point &A, const Point &B, const Point &C) : A(A), B(B), C(C) {}

    float getArea() const;
};

#endif