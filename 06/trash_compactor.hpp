#ifndef __06_TRASH_COMPACTOR_H_
#define __06_TRASH_COMPACTOR_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

#include "parse.hpp"

struct ColInput {
    std::vector<std::string> nums;
    std::string op;

    bool operator==(const ColInput& other) const {
        return nums == other.nums && op == other.op;
    }
};

class Trash_compactor : public Parse {
   private:
    int _mRowSize;
    vector<vector<string>> _mInputParsed;
    void parse_input(void);

   public:
    explicit Trash_compactor(const Input& in);
    long long calcualate(void);
    ColInput get_nums_at_col(int col);
    long long multiply_nums(const ColInput& input);
    long long add_nums(const ColInput& input);
    ~Trash_compactor();
};

#endif  // __06_TRASH_COMPACTOR_H_
