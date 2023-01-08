#include "field.h"
#include "triangle.h"

Field::Field(const Point &A, const Point &B, const Point &C, const Point &D, bool sizeCheck)
{
    setAll(A, B, C, D, sizeCheck);
}

float Field::getLength(const Point A, const Point B) const
{
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

void Field::setAll(const Point &A, const Point &B, const Point &C, const Point &D, bool sizeCheck)
{

    if (getLength(A, B) * 2 != getLength(B, C) && getLength(A, B) != getLength(B, C) * 2 && sizeCheck)
    {
        throw std::invalid_argument("Invalid field size!");
    }

    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
}

float Field::getArea() const
{
    return getLength(A, B) * getLength(B, C);
}

bool Field::isInside(const Point &P) const
{
    Triangle ABC(P, this->A, this->B);
    Triangle ACD(P, this->A, this->C);
    Triangle BCD(P, this->B, this->C);
    Triangle ABD(P, this->A, this->D);

    return ABC.getArea() + ACD.getArea() + BCD.getArea() + ABD.getArea() == getArea();
}

int Field::getBouncesEven(Point *last, Line l1, Line l2, Point p1, Vector v)
{
    int bounces = 0;
    Line parallel((*last), l1.getVector());
    float divider = parallel.getA(), divider2 = l1.getA(), divider4 = l2.getA();
    if (parallel.getA() == 0)
    {
        divider = parallel.getB();
        divider2 = l1.getB();
        divider4 = l2.getB();
    }
    float distance = getLength((*last), p1);

    for (; !((parallel.getC() / divider >= l1.getC() / divider2 && parallel.getC() / divider <= l2.getC() / divider4) || (parallel.getC() / divider <= l1.getC() / divider2 && parallel.getC() / divider >= l2.getC() / divider4)) && bounces < 10; bounces++)
    {
        if (distance < getLength((*last), p1))
        {
            v.reverse();
            bounces -= 2;
        }
        (*last).transform(-v.getX(), -v.getY());
        parallel.setPointAndVector((*last), l1.getVector());
    }
    return bounces;
}

int getBouncesOdd(Point *last, Line l1, Line l2, Point p1, Vector v)
{
    int bounces = 0;
    Line parallel((*last), l1.getVector());
    float divider = parallel.getA(), divider1 = l1.getA(), divider3 = l2.getA();
    if (parallel.getA() == 0)
    {
        divider = parallel.getB();
        divider1 = l1.getB();
        divider3 = l2.getB();
    }
    float distance = getLength((*last), p1);

    for (; !((parallel.getC() / divider >= l1.getC() / divider1 && parallel.getC() / divider <= l2.getC() / divider3) || (parallel.getC() / divider <= l1.getC() / divider1 && parallel.getC() / divider >= l2.getC() / divider3)) && bounces < 10; bounces++)
    {
        if (distance < getLength((*last), p1))
        {
            v.reverse();
            bounces -= 2;
        }
        (*last).transform(v.getX(), v.getY());
        parallel.setPointAndVector((*last), l1.getVector());
    }
    return bounces;
}

void Field::invertCheck(Line ls1, Line ls2, Line ls3, Line ls4, int bouncesEven, int bouncesOdd, Point *last)
{
    float divider2 = ls2.getA(), divider4 = ls4.getA();
    if (divider2 == 0)
    {
        divider2 = ls2.getB();
        divider4 = ls4.getB();
    }

    float divider1 = ls1.getA(), divider3 = ls3.getA();
    if (divider1 == 0)
    {
        divider1 = ls1.getB();
        divider3 = ls3.getB();
    }

    Line sim1(ls1.getA() / divider1, ls1.getB() / divider1, getMiddle(ls1.getC() / divider1, ls3.getC() / divider3));
    Line sim2(ls2.getA() / divider2, ls2.getB() / divider2, getMiddle(ls2.getC() / divider2, ls4.getC() / divider4));

    if (bouncesEven % 2 != 0)
    {
        last->invert(sim2, last)
    }
    if (bouncesOdd % 2 != 0)
    {
        last->invert(sim1, last)
    }
}

void Field::holeCheck(Point cur, Point s, Vector path, Line ls1, Line ls2, Line ls3, Line ls4, Point oldLast, Point *last)
{
    Line pathL(cur, path);

    if (!pathL.isParallel(ls1) && !pathL.isParallel(ls2) && !ls1.liesOn(cur) && !ls2.liesOn(cur))
    {
        Point Intr1, Intr2, Intr3, Intr4;
        Intr1.Intersector(pathL, ls1);
        Intr2.Intersector(pathL, ls2);
        Intr3.Intersector(pathL, ls3);
        Intr4.Intersector(pathL, ls4);

        Vector pathF1(Intr1, Intr3);
        Vector pathF2(Intr2, Intr4);

        Point last1, last2;
        last1 = Intr3;
        last2 = Intr4;

        if (pathF1.one_way(path))
        {
            pathF1.reverse();
            last1 = Intr1;
        }
        if (pathF2.one_way(path))
        {
            pathF2.reverse();
            last2 = Intr2;
        }

        list<Point> points;
        for (; getLength(cur, last1) <= getLength(cur, oldLast); last1.transform(pathF1.getX(), pathF1.getY()))
        {
            points.push_back(last1);
        }

        for (; getLength(cur, last2) <= getLength(cur, oldLast); last2.transform(pathF2.getX(), pathF2.getY()))
        {
            list<Point>::iterator it;
            for (it = points.begin(); it != points.end(); it++)
            {
                if (*it == last2)
                {
                    (*last) = s;
                }
            }
        }
    }
}