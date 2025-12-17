#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "dial_rotator.hpp"
#include "gift_shop.hpp"

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

    std::vector<std::pair<long long, long long>> final_ranges;

    std::string line;
    while (std::getline(input_file_stream, line, ','))
    {
        std::istringstream s(line);
        std::vector<long long> v;
        std::string range;
        while (std::getline(s, range, '-'))
        {
            // get two ints seprated by - in string
            v.push_back(std::stoll(range.c_str()));
        }

        std::pair<long long, long long> p(v[0], v[1]);
        final_ranges.push_back(p);
    }

    GiftShop gs{};

    for (auto it = final_ranges.begin(); it != final_ranges.end(); it++)
    {
        gs.accumulate(it->first, it->second);
    }
    std::cout << "Sum is: " << gs.get_sum() << std::endl;

    return 0;
}