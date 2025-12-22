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
    vector<long long> col_result;
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

INSTANTIATE_TEST_SUITE_P(TEST_SUITE_COMPUTE, VERIFY_CALCULATIONS_FIXTURE,
                         ::testing::Values(COMPUTE_INPUT{
                             .input = {{"123 328  51 64"},
                                       {"45 64  387 23"},
                                       {"6 98  215 314"},
                                       {"*   +   *   +"}},
                             .col_result = {33210, 490, 4243455, 401}

                         }));


// Column 0
TEST_P(VERIFY_CALCULATIONS_FIXTURE, VERIFY_COL0) {
    ColInput expected_col{ {"123", "45", "6"}, "*" };
    ColInput actual_col = _trash->get_nums_at_col(0);
    ASSERT_EQ(actual_col, expected_col);
    ASSERT_EQ(_trash->multiply_nums(actual_col), _input.col_result.at(0));
}

// Column 1
TEST_P(VERIFY_CALCULATIONS_FIXTURE, VERIFY_COL1) {
    ColInput expected_col{ {"328", "64", "98"}, "+" };
    ColInput actual_col = _trash->get_nums_at_col(1);
    ASSERT_EQ(actual_col, expected_col);
    ASSERT_EQ(_trash->add_nums(actual_col), _input.col_result.at(1));
}

// Column 2
TEST_P(VERIFY_CALCULATIONS_FIXTURE, VERIFY_COL2) {
    ColInput expected_col{ {"51", "387", "215"}, "*" };
    ColInput actual_col = _trash->get_nums_at_col(2);
    ASSERT_EQ(actual_col, expected_col);
    ASSERT_EQ(_trash->multiply_nums(actual_col), _input.col_result.at(2));
}

// Column 3
TEST_P(VERIFY_CALCULATIONS_FIXTURE, VERIFY_COL3) {
    ColInput expected_col{ {"64", "23", "314"}, "+" };
    ColInput actual_col = _trash->get_nums_at_col(3);
    ASSERT_EQ(actual_col, expected_col);
    ASSERT_EQ(_trash->add_nums(actual_col), _input.col_result.at(3));
}