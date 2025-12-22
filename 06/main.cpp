#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "file_input.hpp"
#include "trash_compactor.hpp"

using namespace std;

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


    FileInput p{input_file};
    Trash_compactor t {p};
    auto result = t.calcualate();

    PRINT(result);



    return 0;
}