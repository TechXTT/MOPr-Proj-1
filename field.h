#ifndef FIELD_H
#define FIELD_H
#include "point.h"
#include "line.h"

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

    int getBouncesEven(Point *last, Line l1, Line l2, Point p1, Vector v);
    int getBouncesOdd(Point *last, Line l1, Line l2, Point p1, Vector v);

    void invertCheck(Line ls1, Line ls2, Line ls3, Line ls4, int bouncesEven, int bouncesOdd, Point *last);
    void holeCheck(Point cur, Point s, Vector path, Line ls1, Line ls2, Line ls3, Line ls4, Point oldLast, Point *last);

    void getMiddle(float a, floay b) const { return a + (b - a) / 2; }
};

#endif