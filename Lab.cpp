#include <iostream>
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
    std::cout << "Використання: " << programName << " <вхідний_файл> <вихідний_файл>\n";
    std::cout << "\nФормат вхідного файлу:\n";
    std::cout << "Рядок 1: n (кількість точок для генерації)\n";
    std::cout << "Рядок 2: x y (координати початкової точки)\n";
    std::cout << "Рядки 3+: a b c d tx ty (параметри афінного перетворення)\n";
    std::cout << "\nПриклад:\n";
    std::cout << "100000\n";
    std::cout << "0 0\n";
    std::cout << "0.5 0 0 0.5 0 0\n";
    std::cout << "0.5 0 0 0.5 0.5 0\n";
    std::cout << "0.5 0 0 0.5 0.25 0.5\n";
}

void printStatistics(const InputData& data, const std::vector<Point>& points,
    std::chrono::milliseconds executionTime)
{
    std::cout << "\n=== Статистика виконання ===\n";
    std::cout << "Кількість згенерованих точок: " << points.size() << "\n";
    std::cout << "Кількість афінних перетворень: " << data.transforms.size() << "\n";
    std::cout << "Початкова точка: " << data.startPoint << "\n";
    std::cout << "Кінцева точка: " << points.back() << "\n";
    std::cout << "Час виконання: " << executionTime.count() << " мс\n";
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

        std::cout << "=== Програма генерації послідовності точок афінними перетвореннями ===\n";
        std::cout << "Вхідний файл: " << inputFilename << "\n";
        std::cout << "Вихідний файл: " << outputFilename << "\n\n";

        if (!FileHandler::fileExists(inputFilename)) {
            throw std::runtime_error("Вхідний файл не існує: " + inputFilename);
        }

        auto startTime = std::chrono::high_resolution_clock::now();

        std::cout << "Читання вхідних даних...\n";
        InputData data = FileHandler::readInputFile(inputFilename);

        std::cout << "Кількість точок для генерації: " << data.n << "\n";
        std::cout << "Початкова точка: " << data.startPoint << "\n";
        std::cout << "Кількість афінних перетворень: " << data.transforms.size() << "\n";

        std::cout << "Генерація послідовності точок...\n";
        std::vector<Point> points = generatePointSequence(data);

        std::cout << "Запис результату у файл...\n";
        FileHandler::writeOutputFile(outputFilename, points);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        printStatistics(data, points, executionTime);

        std::cout << "\nПрограма успішно завершена!\n";
        return 0;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Невідома помилка!" << std::endl;
        return 1;
    }

    return 0;
}
