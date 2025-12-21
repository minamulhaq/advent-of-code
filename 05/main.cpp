#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "cafeteria.hpp"

using namespace std;
#define PRINT(x) std::cout << (x) << std::endl;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "No input file passed\n";
        return EXIT_FAILURE;
    }
    const std::filesystem::path input_file = argv[1];
    if (!std::filesystem::exists(input_file))
    {
        std::cerr << "Error: Input file doesn't exist: " << input_file.string()
                  << "\n";
        return EXIT_FAILURE;
    }

    std::ifstream input_file_stream(input_file);
    if (!input_file_stream.is_open())
    {
        std::cerr << "Error: Failed to open input file stream.\n";
        return EXIT_FAILURE;
    }

    std::string line;
    ID_RANGES ranges;
    IDS ids;
    bool ranges_ended = false;
    while (std::getline(input_file_stream, line))
    {
        istringstream ss(line);
        if (line.empty())
        {
            ranges_ended = true;
            continue;
        }

        if (ranges_ended)
        {
            ID id;
            ss >> id;
            ids.emplace_back(id);
        }

        else
        {
            long long range1, range2;
            char dash;
            ss >> range1 >> dash >> range2;
            ranges.emplace_back(pair(range1, range2));
        }
    }

    Cafeteria cafe{};
    PRINT(cafe.count_fresh(ranges));


    return 0;
}