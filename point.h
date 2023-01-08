#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <cmath>

struct Point
{
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    void setPoint(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void transform(float x, float y)
    {
        this->x += x;
        this->y += y;
    }

    void invert(Line l1, Point p1)
    {
        cout << "Inverter Line: " << l1 << endl;
        if (l1.getB() == 0)
        {
            float lineX = -l1.getC() / l1.getA();
            (*this).setPoint(lineX + (lineX - p1.x), p1.y);
            cout << "Point: " << (*this) << endl;
            return;
        }
        float eq1 = p1.y * l1.getA() * l1.getB();
        float eq2 = p1.x * pow(l1.getB(), 2);
        float eq3 = l1.getA() * l1.getC();
        float eq4 = pow(l1.getA(), 2) + pow(l1.getB(), 2);
        float eq5 = ((-eq1 + eq2 - eq3) / eq4);

        float x = 2 * eq5 - p1.x;
        float y = (-2 * (l1.getC() + l1.getA() * eq5) / l1.getB()) - p1.y;
        (*this).setPoint(x, y);
    }

    void Intersector(Line path, Line ls)
    {
        if (path.isParallel(ls))
        {
            return;
        }
        if (path.getB() == 0)
        {
            float x = path.getC() / path.getA();
            float y = (ls.getA() + ls.getC()) / -ls.getB();
            (*this).setPoint(x, y);
            return;
        }
        else if (ls.getB() == 0)
        {
            float x = ls.getC() / ls.getA();
            float y = (path.getA() + path.getC()) / -path.getB();
            (*this).setPoint(x, y);
            return;
        }

        float eqA1 = path.getA() / path.getB(), eqC1 = path.getC() / path.getB();
        float eqA2 = ls.getA() / ls.getB(), eqC2 = ls.getC() / ls.getB();

        float x = (eqC1 - eqC2) / (eqA2 - eqA1);
        float y = (path.getA() * x + path.getC()) / -path.getB();
        (*this).setPoint(x, y);
    }
};

// this is for inputing a point
inline std::istream &operator>>(std::istream &in, Point &p)
{
    in >> p.x;
    in >> p.y;

    return in;
}

// this is for printing a point
inline std::ostream &operator<<(std::ostream &out, Point &p)
{
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

#endif