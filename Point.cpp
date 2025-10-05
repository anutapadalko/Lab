#include "Point.h"

Point& Point::operator=(const Point& other)
{
    if (this != &other)
    {
        value_ = other.value_;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << std::fixed << std::setprecision(6)
        << p.value_.real() << " " << p.value_.imag();
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    double x, y;
    if (is >> x >> y) {
        p.value_ = { x, y };
    }
    return is;
}