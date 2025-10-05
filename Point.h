#pragma once

#include <iostream>
#include <iomanip>
#include <complex>

class Point {
private:
    std::complex<double> value_;

public:
    Point() : value_(0.0, 0.0) {}
    Point(double x, double y) : value_(x, y) {}

    Point(const Point& other) : value_(other.value_) {}

    Point& operator=(const Point& other);

    double getX() const { return value_.real(); }
    double getY() const { return value_.imag(); }

    void setX(double x) { value_ = { x, value_.imag() }; }
    void setY(double y) { value_ = { value_.real(), y }; }
    void setPoint(double x, double y) { value_ = { x, y }; }

    const std::complex<double>& getValue() const { return value_; }

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
};