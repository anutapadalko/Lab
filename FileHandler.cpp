#include "FileHandler.h"

InputData FileHandler::readInputFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Program couldn't open the file: " + filename);
    }

    InputData data;

    if (!(file >> data.n))
    {
        throw std::runtime_error("Error while reading number of points from the file");
    }

    if (data.n == 0)
    {
        throw std::invalid_argument("Number of points has to be greater than 0");
    }

    if (!(file >> data.startPoint))
    {
        throw std::runtime_error("Error while reading start point from the file");
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
        throw std::runtime_error("No affine transform was found in the file");
    }

    return data;
}

void FileHandler::writeOutputFile(const std::string& filename, const std::vector<Point>& points)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Couldn't create file: " + filename);
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
