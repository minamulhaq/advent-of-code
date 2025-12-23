#ifndef __06_TRASH_COMPACTOR_H_
#define __06_TRASH_COMPACTOR_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

#include "parse.hpp"

enum Operation { ADD, MUL, NO_OP, SKIP };

struct ColOutput {
    int number;
    Operation op;

    inline bool operator==(const ColOutput& other) const {
        return (number == other.number) && (op == other.op);
    }

    bool operator!=(const ColOutput& other) const { return !(*this == other); }
};

class Trash_compactor : public Parse {
   private:
    long long _result;
    vector<string>lines;
    vector<vector<string>> _mInputParsed;
    void parse_input(void);

   public:
    long long get_result(void);
    explicit Trash_compactor(const Input& in);
    ColOutput get_col_output(const int& col_num);
    ~Trash_compactor();
};

#endif  // __06_TRASH_COMPACTOR_H_
