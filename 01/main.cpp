#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

#include "dial_rotator.hpp"



int main(int argc, char** argv) {
    // ... (File handling remains unchanged) ...

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

    // Start dial at 50 as required
    DialRotator rotator{50};

    std::ifstream input_file_stream(input_file);
    if (!input_file_stream.is_open()) {
        std::cerr << "Error: Failed to open input file stream.\n";
        return EXIT_FAILURE;
    }

    std::string line;
    while (std::getline(input_file_stream, line)) {
        rotator.rotate(line);
    }

    int password = rotator.get_zero_count();
    std::cout << "Actual Password (Total Zero Clicks): " << password << "\n";

    return 0;
}