#pragma once

#include "Point.h"
#include "AffineTransform.h"
#include <vector>
#include <random>
#include <stdexcept>

class RandomTransformer
{
private:
    std::vector<AffineTransform> transforms_;
    mutable std::mt19937 generator_;
    mutable std::uniform_int_distribution<size_t> distribution_;

public:
    RandomTransformer() : generator_(std::random_device{}()) {}

    explicit RandomTransformer(const std::vector<AffineTransform>& transforms)
        : transforms_(transforms), generator_(std::random_device{}())
    {
        if (transforms_.empty())
        {
            throw std::invalid_argument("RandomTransformer: список перетворень не може бути порожнім");
        }
        distribution_ = std::uniform_int_distribution<size_t>(0, transforms_.size() - 1);
    }

    void addTransform(const AffineTransform& transform);

    void clearTransforms();

    bool isEmpty() const;

    size_t size() const;

    Point operator()(const Point& point) const;

    void setSeed(unsigned int seed);

    const AffineTransform& getTransform(size_t index) const;
};

