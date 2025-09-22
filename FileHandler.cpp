#include "FileHandler.h"

InputData FileHandler::readInputFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Не вдалося відкрити файл: " + filename);
    }

    InputData data;

    if (!(file >> data.n))
    {
        throw std::runtime_error("Помилка читання кількості точок з файлу");
    }

    if (data.n == 0)
    {
        throw std::invalid_argument("Кількість точок повинна бути більше 0");
    }

    if (!(file >> data.startPoint))
    {
        throw std::runtime_error("Помилка читання початкової точки з файлу");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::array<double, 6> params;

        bool validLine = true;
        for (int i = 0; i < 6; ++i)
        {
            if (!(iss >> params[i]))
            {
                validLine = false;
                break;
            }
        }

        if (validLine)
        {
            data.transforms.emplace_back(params);
        }
    }

    file.close();

    if (data.transforms.empty())
    {
        throw std::runtime_error("Не знайдено жодного афінного перетворення у файлі");
    }

    return data;
}

void FileHandler::writeOutputFile(const std::string& filename, const std::vector<Point>& points)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Не вдалося створити файл: " + filename);
    }

    for (const auto& point : points)
    {
        file << point << '\n';
    }

    file.close();
}

bool FileHandler::fileExists(const std::string& filename)
{
    std::ifstream file(filename);
    return file.good();
}
