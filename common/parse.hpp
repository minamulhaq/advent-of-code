
#ifndef __COMMON_PARSE_H_
#define __COMMON_PARSE_H_
#include <memory>

#include "input.hpp"

class Parse {
   protected:
    const Input& _mIn;

   public:
    explicit Parse(const Input& in);
    virtual void parse_input(void) = 0;
    virtual ~Parse() = default;
};

#endif  // __COMMON_PARSE_H_
