#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "joltage.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "No input file passed\n";
        return EXIT_FAILURE;
    }
    const std::filesystem::path input_file = argv[1];
    if (!std::filesystem::exists(input_file)) {
        std::cerr << "Error: Input file doesn't exist: " << input_file.string()
                  << "\n";
        return EXIT_FAILURE;
    }

    std::ifstream input_file_stream(input_file);
    if (!input_file_stream.is_open()) {
        std::cerr << "Error: Failed to open input file stream.\n";
        return EXIT_FAILURE;
    }

    std::string line;
    vector<string> lines;
    while (std::getline(input_file_stream, line)) {
        lines.emplace_back(line);
    }
    Joltage j{};

    for (auto l : lines) {
        j.parse_voltages_from_line(l);
    }


    cout << "Total Joltage: " << j.get_total_joltage() << endl;

    return 0;
}