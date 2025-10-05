#pragma once
// Compiler: MVC with C++20 support

#include "Point.h"
#include "AffineTransform.h"
#include "RandomTransformer.h"
#include "FileHandler.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>

std::vector<Point> generatePointSequence(const InputData& data)
{
    std::vector<Point> points;
    points.reserve(data.n);

    RandomTransformer transformer(data.transforms);

    Point currentPoint = data.startPoint;
    points.push_back(currentPoint);

    for (size_t i = 1; i < data.n; ++i)
    {
        currentPoint = transformer(currentPoint);
        points.push_back(currentPoint);
    }

    return points;
}

void printUsage(const std::string& programName)
{
    std::cout << "Using: " << programName << " <input_file> <output_file>\n";
    std::cout << "\nFormat of the input file:\n";
    std::cout << "Line 1: n (number of points for generation)\n";
    std::cout << "Line 2: x y (coordinates of start point)\n";
    std::cout << "Lines 3+: a b c d tx ty (parameters of the affine transformation)\n";
    std::cout << "\nExample:\n";
    std::cout << "100000\n";
    std::cout << "0 0\n";
    std::cout << "0.5 0 0 0.5 0 0\n";
    std::cout << "0.5 0 0 0.5 0.5 0\n";
    std::cout << "0.5 0 0 0.5 0.25 0.5\n";
}

void printStatistics(const InputData& data, const std::vector<Point>& points,
    std::chrono::milliseconds executionTime)
{
    std::cout << "\n=== Statistics of executing ===\n";
    std::cout << "Number of generated points: " << points.size() << "\n";
    std::cout << "Number of affine transform: " << data.transforms.size() << "\n";
    std::cout << "Start point: " << data.startPoint << "\n";
    std::cout << "End point: " << points.back() << "\n";
    std::cout << "Time of execution: " << executionTime.count() << " мс\n";
}

int main(int argc, char* argv[])
{
    std::setlocale(LC_ALL, "uk_UA.UTF-8");
    try {
        if (argc != 3)
        {
            printUsage(argv[0]);
            return 1;
        }

        std::string inputFilename = argv[1];
        std::string outputFilename = argv[2];

        std::cout << "=== Program that generates list of points with the affine transform ===\n";
        std::cout << "Input file: " << inputFilename << "\n";
        std::cout << "Output file: " << outputFilename << "\n\n";

        if (!FileHandler::fileExists(inputFilename)) {
            throw std::runtime_error("Input file does not exist: " + inputFilename);
        }

        auto startTime = std::chrono::high_resolution_clock::now();

        std::cout << "Reading of input data...\n";
        InputData data = FileHandler::readInputFile(inputFilename);

        std::cout << "Number of points for generation: " << data.n << "\n";
        std::cout << "Start point: " << data.startPoint << "\n";
        std::cout << "Number of affine transformations: " << data.transforms.size() << "\n";

        std::cout << "Generating list of points...\n";
        std::vector<Point> points = generatePointSequence(data);

        std::cout << "Writing result to the file...\n";
        FileHandler::writeOutputFile(outputFilename, points);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        printStatistics(data, points, executionTime);

        std::cout << "\nProgram has successfully ended!\n";
        return 0;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error!" << std::endl;
        return 1;
    }

    return 0;
}