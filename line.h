#ifndef LINE_H
#define LINE_H

#include "vector.h"

class Line
{
    int A, B, C;

public:
    Line(int A = 0, int B = 0, int C = 0) : A(A), B(B), C(C) {}
    Line(const Point p, const Vector &v);
    Line(const Point p1, const Point p2);
    Line(Field f, Line l1, Line l2, Point p1);

    Vector getVector() const;
    void setPoints(const Point p1, const Point p2);

    friend std::ostream &operator<<(std::ostream &out, const Line &l);
    friend std::istream &operator>>(std::istream &in, Line &l);
};

inline std::ostream &operator<<(std::ostream &out, const Line &l)
{
    out << l.A << "x + " << l.B << "y + " << l.C << " = 0 ";
    return out;
}

inline std::istream &operator>>(std::istream &in, Line &l)
{
    in >> l.A;
    in >> l.B;
    in >> l.C;
    return in;
}

#endif