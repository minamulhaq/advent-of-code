#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

#include "gtest/gtest.h"
#include "trash_compactor.hpp"

using namespace std;

struct COMPUTE_INPUT {
    vector<string> input;
    int col;
    ColOutput colOut;
};

class TestInput : public Input {
   private:
    vector<string> _mLines;

   public:
    TestInput(const vector<string>& strings) : _mLines(strings) {}
    vector<string> input(void) const { return _mLines; };
    ~TestInput() {}
};

class VERIFY_CALCULATIONS_FIXTURE
    : public ::testing::TestWithParam<COMPUTE_INPUT> {
   protected:
    unique_ptr<Trash_compactor> _trash;
    COMPUTE_INPUT _input;
    void SetUp() override {
        _input = GetParam();
        TestInput tinput{_input.input};
        _trash = make_unique<Trash_compactor>(tinput);
    }
    void TearDown() override {}
};

INSTANTIATE_TEST_SUITE_P(
    TEST_SUITE_COMPUTE, VERIFY_CALCULATIONS_FIXTURE,
    ::testing::Values(COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    0,
                                    {1, MUL}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    1,
                                    {24, NO_OP}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    2,
                                    {356, NO_OP}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    3,
                                    {0, SKIP}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    4,
                                    {369, ADD}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    5,
                                    {248, NO_OP}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    6,
                                    {8, NO_OP}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    7,
                                    {0, SKIP}},

                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    8,
                                    {32, MUL}},

                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    9,
                                    {581, NO_OP}},

                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    10,
                                    {175, NO_OP}},

                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    11,
                                    {0, SKIP}},

                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    12,
                                    {623, ADD}},

                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    13,
                                    {431, NO_OP}},
                      COMPUTE_INPUT{{"123 328  51 64 ", " 45 64  387 23 ",
                                     "  6 98  215 314", "*   +   *   +  "},
                                    14,
                                    {4, NO_OP}}

                      ));

TEST_P(VERIFY_CALCULATIONS_FIXTURE, VERIFY_COL0) {
    ColOutput actual = _trash->get_col_output(_input.col);

    std::cout << "DEBUG: Column " << _input.col << "\n";
    std::cout << "  Expected number: " << _input.colOut.number
              << ", Actual number: " << actual.number << "\n";

    auto op_to_str = [](Operation op) -> std::string {
        switch (op) {
            case ADD:
                return "+";
            case MUL:
                return "*";
            case NO_OP:
                return "NO_OP";
        }
        return "?";
    };

    std::cout << "  Expected op: " << op_to_str(_input.colOut.op)
              << ", Actual op: " << op_to_str(actual.op) << "\n";

    ASSERT_EQ(actual.number, _input.colOut.number);
    ASSERT_EQ(actual.op, _input.colOut.op);
}
