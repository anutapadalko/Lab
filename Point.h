#pragma once

#include <iostream>
#include <iomanip>

class Point
{
private:
    double x_;
    double y_;

public:
    Point() : x_(0.0), y_(0.0) {}
    Point(double x, double y) : x_(x), y_(y) {}

    Point(const Point& other) : x_(other.x_), y_(other.y_) {}

    Point& operator=(const Point& other);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);
    void setPoint(double x, double y);

    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    friend std::istream& operator>>(std::istream& is, Point& p);
};

