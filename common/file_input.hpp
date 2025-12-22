
#ifndef __COMMON_FILE_INPUT_H_
#define __COMMON_FILE_INPUT_H_

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "input.hpp"

using namespace std;

#define PRINT(x) std::cout << (x) << std::endl;

class FileInput : public Input {
   private:
    filesystem::path _mFile;
    vector<string> _mLines;
    bool ReadInputFile(void);

   public:
    vector<string> input(void) const override;
    explicit FileInput(const ::filesystem::path& input_file);
    virtual ~FileInput();
};

#endif  // __COMMON_FILE_INPUT_H_
