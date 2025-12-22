#include "trash_compactor.hpp"

#include <assert.h>

#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace std;

Trash_compactor::Trash_compactor(const Input& in) : Parse(in) { parse_input(); }

Trash_compactor::~Trash_compactor(void) {}

void Trash_compactor::parse_input(void) {
    vector<string> lines = _mIn.input();
    for (auto line : lines) {
        istringstream f(line);
        vector<string> numbers_line;
        string s;
        while (getline(f, s, ' ')) {
            if (!s.empty()) {
                numbers_line.push_back(s);
            }
        }
        _mInputParsed.emplace_back(numbers_line);
    }

    _mRowSize = _mInputParsed.at(0).size();
    for (auto l : _mInputParsed) {
        assert(_mRowSize == l.size());
    }
}

long long Trash_compactor::multiply_nums(const ColInput& input) {
    long long result = 1;
    for (auto n : input.nums) {
        result *= stoll(n);
    }
    return result;
}

long long Trash_compactor::add_nums(const ColInput& input) {
    long long result = 0;
    for (auto n : input.nums) {
        result += stoll(n);
    }
    return result;
}

long long Trash_compactor::calcualate(void) {
    long long total = 0;

    auto symbols = _mInputParsed.back();

    for (auto i = 0; i < _mRowSize; i++) {
        ColInput colInput = get_nums_at_col(i);
        auto symbol = colInput.op;

        if (symbol == "*") {
            total += multiply_nums(colInput);
        } else if (symbol == "+") {
            total += add_nums(colInput);
        }
    }
    return total;
}

ColInput Trash_compactor::get_nums_at_col(int col) {
    vector<string> nums;
    string operation;

    for (auto i = 0; i < _mInputParsed.size() - 1; i++) {
        nums.emplace_back(_mInputParsed.at(i).at(col));
    }
    operation = _mInputParsed.back().at(col);

    return ColInput{.nums = nums, .op = operation};
}
