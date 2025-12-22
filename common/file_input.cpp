#include "file_input.hpp"

#include <fstream>
#include <format>

using namespace std;

FileInput::FileInput(const ::filesystem::path& input_file)
    : _mFile(input_file) {
    ReadInputFile();
}

bool FileInput::ReadInputFile(void) {
    ifstream input_file_stream(_mFile);
    if (!input_file_stream.is_open()) {
        return false;
    }

    std::string line;
    bool ranges_ended = false;
    while (std::getline(input_file_stream, line)) {
        _mLines.emplace_back(line);
    }
    std::cout << format("Total {} lines read in {}\n", _mLines.size(), "FileInput");
    return true;
}

FileInput::~FileInput() {}


vector<string> FileInput::input(void) const { return _mLines; }
