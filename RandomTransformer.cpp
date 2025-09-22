#include "RandomTransformer.h"

void RandomTransformer::addTransform(const AffineTransform& transform)
{
    transforms_.push_back(transform);
    distribution_ = std::uniform_int_distribution<size_t>(0, transforms_.size() - 1);
}

void RandomTransformer::clearTransforms()
{
    transforms_.clear();
}

bool RandomTransformer::isEmpty() const
{
    return transforms_.empty();
}

size_t RandomTransformer::size() const
{
    return transforms_.size();
}

Point RandomTransformer::operator()(const Point& point) const
{
    if (transforms_.empty())
    {
        throw std::runtime_error("RandomTransformer: немає доступних перетворень");
    }

    size_t index = distribution_(generator_);

    return transforms_[index].apply(point);
}

void RandomTransformer::setSeed(unsigned seed)
{
    generator_.seed(seed);
}

const AffineTransform& RandomTransformer::getTransform(size_t index) const
{
    if (index >= transforms_.size())
    {
        throw std::out_of_range("RandomTransformer: індекс поза межами");
    }
    return transforms_[index];
}

