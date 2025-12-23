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

long long Trash_compactor::get_result(void) { return _result; }

void Trash_compactor::parse_input(void) {
    _result = 0;
    lines = _mIn.input();
    for (auto l : lines) {
        cout << format("line size: {}\n", l.size());
    }
    int range = lines.front().size();

    vector<int> numbers;
    for (int i = range - 1; i >= 0; i--) {
        ColOutput out = get_col_output(i);

        switch (out.op) {
            case ADD: {
                cout << format("operation ADD\n");
                numbers.emplace_back(out.number);
                for (auto n : numbers) {
                    cout << format("Numbers {}\n", n);
                    _result += n;
                }
                break;
            }
            case MUL: {
                numbers.emplace_back(out.number);
                cout << format("operation MUL\n");
                long long r = 1;
                for (auto n : numbers) {
                    cout << format("Numbers {}\n", n);
                    r *= n;
                }
                _result += r;
                break;
            }
            case NO_OP: {
                numbers.emplace_back(out.number);
                break;
            }
            case SKIP: {
                numbers.clear();
                break;
            }

            default:
                break;
        }
    }
    cout << format("Result is : {}\n", _result);
}

ColOutput Trash_compactor::get_col_output(const int& col_num) {
    cout << format("Calucating colout at col number : {}\n", col_num);
    ColOutput out{.number = 0, .op = NO_OP};

    Operation op;
    vector<char> vchar;
    for (auto l : lines) {
        vchar.emplace_back(l.at(col_num));
    }
    char operation = vchar.back();
    vchar.pop_back();

    switch (operation) {
        case ' ': {
            op = NO_OP;
            break;
        }
        case '+': {
            op = ADD;
            break;
        }
        case '*': {
            op = MUL;
            break;
        }
        default: {
            op = NO_OP;
            break;
        }
    }
    string num = "";

    for (auto c : vchar) {
        if (' ' != c) {
            num += c;
        }
    }

    if (num.empty()) {
        out.op = SKIP;
        return out;
    }

    out.number = stoll(num);
    out.op = op;
    return out;
}
