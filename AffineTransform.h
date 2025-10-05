#pragma once

#include "Point.h"
#include <array>

class AffineTransform {
private:
    std::array<std::array<double, 2>, 2> matrix_;
    std::array<double, 2> translation_;

public:
    AffineTransform()
        : matrix_{ {{1.0, 0.0}, {0.0, 1.0}} }, translation_{ 0.0, 0.0 } {
    }

    AffineTransform(double a, double b, double c, double d, double tx, double ty)
        : matrix_{ {{a, b}, {c, d}} }, translation_{ tx, ty } {
    }

    AffineTransform(const std::array<double, 6>& params)
        : matrix_{ {{params[0], params[1]}, {params[2], params[3]}} },
        translation_{ params[4], params[5] } {
    }

    Point apply(const Point& p) const
    {
        auto z = p.getValue();
        double newX = matrix_[0][0] * z.real() + matrix_[0][1] * z.imag() + translation_[0];
        double newY = matrix_[1][0] * z.real() + matrix_[1][1] * z.imag() + translation_[1];

        return Point(newX, newY);
    }
};