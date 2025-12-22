#ifndef __COMMON_INPUT_H_
#define __COMMON_INPUT_H_

#include <vector>
#include <string>
#include <memory>
using namespace std;

class Input
{
public:
    virtual vector<string> input(void) const = 0;
    virtual~Input() = default;
};

#endif // __COMMON_INPUT_H_
