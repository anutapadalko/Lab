#include "Point.h"

Point& Point::operator=(const Point& other)
{
    if (this != &other)
    {
        x_ = other.x_;
        y_ = other.y_;
    }
    return *this;
}

double Point::getX() const
{
    return x_;
}

double Point::getY() const
{
    return y_;
}

void Point::setX(double x)
{
    x_ = x;
}

void Point::setY(double y)
{
    y_ = y;
}

void Point::setPoint(double x, double y)
{
    x_ = x;
    y_ = y;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << std::fixed << std::setprecision(6) << p.x_ << " " << p.y_;
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x_ >> p.y_;
    return is;
}
