#include "line.h"

// TODO - constructs a line given a point and a vector - Конструира права по дадени точка и вектор
Line::Line(const Point p, const Vector &v)
{
    A = v.y;
    B = -v.x;
    C = -A * p.x - B * p.y;
}

Line::Line(Field f, Line l1, Line l2, Point p1)
{
    Vector v1(f, l1.getVector(), l2.getVector(), p1);
    A = v1.y;
    B = -v1.x;
    C = -A * p1.x - B * p1.y;
}

// TODO - constructs a line given two points - Конструира права по дадени две точки*
// Задавам си две точки и използвам формулата за права, която се получава от две точки
Line::Line(const Point p1, const Point p2)
{
    A = p2.y - p1.y;
    B = p1.x - p2.x;
    C = -A * p1.x - B * p1.y;
}

void Line::setPoints(const Point p1, const Point p2)
{
    A = p2.y - p1.y;
    B = p1.x - p2.x;
    C = -A * p1.x - B * p1.y;
}

void Line::setPointAndVector(const Point p, const Vector &v)
{
    A = v.y;
    B = -v.x;
    C = -A * p.x - B * p.y;
}

Vector Line::getVector() const
{
    return Vector(-B, A);
}

bool Line::isParallel(const Line &l) const
{
    return (A * l.B == B * l.A);
}

bool Line::liesOn(const Point &p) const
{
    return (A * p.x + B * p.y + C == 0);
}