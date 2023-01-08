#include "vector.h"

// TODO - constructs vector from 2 points - Конструира вектор по подадени две точки (с координати във второто измерение), посоката му е от първата точка към втората
Vector::Vector(const Point p1, const Point p2)
{
    this->x = p2.x - p1.x;
    y = p2.y - p1.y;
}

Vector::Vector(Field f, Vector v1, Vector v2, Point intr)
{
    float x1 = v1.x;
    float y1 = v1.y;
    float x2 = v2.x * v1.length() / v2.length();
    float y2 = v2.y * v1.length() / v2.length();

    this->x = x1 + x2;
    this->y = y1 + y2;

    while (true)
    {
        Point p(intr.x + this->x, intr.y + this->y);

        if (f.isInside(p))
        {
            break;
        }

        v2.reverse();
        x2 = v2.x * v1.length() / v2.length();
        y2 = v2.y * v1.length() / v2.length();

        this->x = x1 + x2;
        this->y = y1 + y2;

        p.setPoint(intr.x + this->x, intr.y + this->y);

        if (f.isInside(p))
        {
            break;
        }

        v1.reverse();
        x1 = v1.x;
        y1 = v1.y;

        this->x = x1 + x2;
        this->y = y1 + y2;

        p.setPoint(intr.x + this->x, intr.y + this->y);

        if (f.isInside(p))
        {
            break;
        }

        v2.reverse();
        x2 = v2.x * v1.length() / v2.length();
        y2 = v2.y * v1.length() / v2.length();

        this->x = x1 + x2;
        this->y = y1 + y2;

        p.setPoint(intr.x + this->x, intr.y + this->y);

        if (f.isInside(p))
        {
            break;
        }
        v1.half();
        v2.half();
    }
}

// TODO - returns the sum of two vectors (which is also e vector) - Връща нов вектор, представляващ сумата на сегашния вектор и подаденият на метода вектор
Vector Vector::sum(const Vector &other) const
{
    Vector result;
    result.x = this->x + other.x;
    result.y = y + other.y;
    return result;
}

// TODO - returns the product of a vector and a number (which is also e vector) - Връща нов вектор, представляващ произведението на сегашния вектор и подаденото на метода число
Vector Vector::times_num(float num) const
{
    Vector result;
    result.x = this->x * num;
    result.y = y * num;
    return result;
}

// TODO - returns a boolean value, answering the question whether the current - Проверява дали сегашният вектор е колинеарен на подадения* вектор
// vector and another ("other") are collinear
// Използваме формулата за колинеарност на вектори, която е:
// a1 * b2 - a2 * b1 = 0
bool Vector::is_colinear(const Vector &other) const
{
    return this->x * other.y == this->y * other.x;
}

// TODO - returns the length of the current vector - Връща дължината на сегашния вектор
double Vector::length() const
{
    return sqrt(this->x * this->x + y * y);
}

double Vector::HeronFormula(const Vector &other) const
{
    return sqrt((this->x + other.x) * (this->x + other.x) + (y + other.y) * (y + other.y));
}

void Vector::setPoints(const Point p1, const Point p2)
{
    this->x = p2.x - p1.x;
    this->y = p2.y - p1.y;
}

bool Vector::one_way(const Vector &other) const
{
    return this->x * other.y - this->y * other.x > 0;
}

void Vector::reverse()
{
    this->x = -this->x;
    this->y = -this->y;
}

void Vector::half()
{
    this->x /= 2;
    this->y /= 2;
}