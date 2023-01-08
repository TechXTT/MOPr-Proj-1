#include "triangle.h"

float Triangle::getArea() const
{
    return abs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2);
}