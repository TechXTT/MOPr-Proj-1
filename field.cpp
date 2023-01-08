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