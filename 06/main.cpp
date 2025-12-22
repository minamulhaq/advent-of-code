#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

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
    bool ranges_ended = false;
    while (std::getline(input_file_stream, line))
    {
        PRINT(line);

    }

    return 0;
}