#pragma once

#include "Point.h"
#include "AffineTransform.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>


struct InputData {
    size_t n;
    Point startPoint;
    std::vector<AffineTransform> transforms;

};

class FileHandler
{
public:
    static InputData readInputFile(const std::string& filename);

    static void writeOutputFile(const std::string& filename, const std::vector<Point>& points);

    static bool fileExists(const std::string& filename);

private:
    FileHandler() = default;
};

