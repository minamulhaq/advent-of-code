#include "gtest/gtest.h"
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include "pdept.hpp"

using namespace std;

struct GRID_TEST_CASE_INPUT
{
    GRID grid;
    int rows;
    int cols;
    int expected_rolls;
};

struct IsRollCase
{
    GRID grid;
    int row;
    int col;
    bool expected;
};

class PDepartmentTest : public ::testing::TestWithParam<GRID_TEST_CASE_INPUT>
{

protected:
    std::unique_ptr<PDepartment> _mpdept;
    GRID_TEST_CASE_INPUT input;

    void SetUp() override
    {
        input = GetParam();
        _mpdept = std::make_unique<PDepartment>(input.grid);
    }
    void TearDown() override {}
};

INSTANTIATE_TEST_SUITE_P(
    ExampleFromProblem,
    PDepartmentTest,
    ::testing::Values(
        GRID_TEST_CASE_INPUT{
            {"..@@.@@@@.",
             "@@@.@.@.@@",
             "@@@@@.@.@@",
             "@.@@@@..@.",
             "@@.@@@@.@@",
             ".@@@@@@@.@",
             ".@.@.@.@@@",
             "@.@@@.@@@@",
             ".@@@@@@@@.",
             "@.@.@@@.@."},
            10,
            10,
            13}));

TEST_P(PDepartmentTest, ConstructorTest)
{
    ASSERT_NE(_mpdept, nullptr);
    ASSERT_EQ(_mpdept->rows(), static_cast<int>(input.grid.size()));
    ASSERT_EQ(_mpdept->cols(), static_cast<int>(input.grid[0].size()));
}

class IsRollTest : public ::testing::TestWithParam<IsRollCase>
{
protected:
    std::unique_ptr<PDepartment> _mpdept;
    IsRollCase input;

    void SetUp() override
    {
        input = GetParam();
        _mpdept = std::make_unique<PDepartment>(input.grid);
    }
    void TearDown() override {}
};
INSTANTIATE_TEST_SUITE_P(
    IsRollCases,
    IsRollTest,
    ::testing::Values(
        IsRollCase{{"@."}, 0, 0, true},
        IsRollCase{{"x."}, 0, 0, false},
        IsRollCase{{"@."}, 0, 1, false}));

TEST_P(IsRollTest, IsRollWorksCorrectly)
{
    EXPECT_EQ(_mpdept->is_roll(input.row, input.col), input.expected);
}

struct IsValidCase
{
    GRID grid;
    INDEX n;
    bool expected;
};

class IsValidTest : public ::testing::TestWithParam<IsValidCase>
{
protected:
    std::unique_ptr<PDepartment> _mpdept;
    IsValidCase input;

    void SetUp() override
    {
        input = GetParam();
        _mpdept = std::make_unique<PDepartment>(input.grid);
    }
};

TEST_P(IsValidTest, ValidatesBoundsCorrectly)
{
    EXPECT_EQ(_mpdept->is_valid(input.n), input.expected);
}
INSTANTIATE_TEST_SUITE_P(
    IsValidCases,
    IsValidTest,
    ::testing::Values(
        IsValidCase{{"@@", "@@"}, {0, 0}, true},
        IsValidCase{{"@@", "@@"}, {1, 1}, true},
        IsValidCase{{"@@", "@@"}, {-1, 0}, false},
        IsValidCase{{"@@", "@@"}, {0, 2}, false},
        IsValidCase{{"@@", "@@"}, {2, 0}, false}));

struct GetNeigboursInput
{
    GRID grid;
    INDEX current;
    INDEXES n;
    int total_neighbours;
};

class CorrectNeighboursTest : public ::testing::TestWithParam<GetNeigboursInput>
{
protected:
    std::unique_ptr<PDepartment> _mpdept;
    GetNeigboursInput input;

    void SetUp() override
    {
        input = GetParam();
        _mpdept = std::make_unique<PDepartment>(input.grid);
    }
};

TEST_P(CorrectNeighboursTest, ValidateCorrectNeighbours)
{
    auto got = _mpdept->get_neighbours(input.current);
    auto expected = input.n;

    std::sort(got.begin(), got.end());
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(got, expected);
    EXPECT_EQ(got.size(), input.total_neighbours);
}

INSTANTIATE_TEST_SUITE_P(
    ValidNeighboursTestCases,
    CorrectNeighboursTest,
    ::testing::Values(
        // Top-left corner (0,0) of 3x3 grid
        GetNeigboursInput{
            {"@..",
             "...",
             "..@"},                  // grid
            {0, 0},                   // current cell
            {{0, 1}, {1, 0}, {1, 1}}, // expected neighbours
            3                         // total neighbours
        },
        // Top-right corner (0,2) of 3x3 grid
        GetNeigboursInput{
            {"@..",
             "...",
             "..@"},
            {0, 2},
            {{0, 1}, {1, 1}, {1, 2}},
            3},
        // Center (1,1) of 3x3 grid
        GetNeigboursInput{
            {"@..",
             "...",
             "..@"},
            {1, 1},
            {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}, {2, 2}},
            8},
        // Bottom-right corner (2,2)
        GetNeigboursInput{
            {"@..",
             "...",
             "..@"},
            {2, 2},
            {{1, 1}, {1, 2}, {2, 1}},
            3},
        // Edge cell (0,1)
        GetNeigboursInput{
            {"@..",
             "...",
             "..@"},
            {0, 1},
            {{0, 0}, {0, 2}, {1, 0}, {1, 1}, {1, 2}},
            5}));

struct GetRollsAroundInput
{
    GRID grid;
    INDEX index;
    int rolls_around;
};

class CorrectRollsAroundTest : public ::testing::TestWithParam<GetRollsAroundInput>
{
protected:
    std::unique_ptr<PDepartment> _mpdept;
    GetRollsAroundInput input;

    void SetUp() override
    {
        input = GetParam();
        _mpdept = std::make_unique<PDepartment>(input.grid);
    }
};

TEST_P(CorrectRollsAroundTest, ValidateCorrectNeighbours)
{
    auto got = _mpdept->get_roll_around_index(input.index);
    auto expected = input.rolls_around;

    EXPECT_EQ(got, expected);
    EXPECT_EQ(got, input.rolls_around);
}

INSTANTIATE_TEST_SUITE_P(
    ValidateCorrectRollsAround,
    CorrectRollsAroundTest,
    ::testing::Values(
        // Center surrounded by rolls -> 8
        GetRollsAroundInput{
            {"@@@",
             "@.@",
             "@@@"},
            {1, 1},
            8},

        // Center with diagonal rolls only -> 4
        GetRollsAroundInput{
            {"@.@",
             ".@.",
             "@.@"},
            {1, 1},
            4},

        // Corner case -> 1
        GetRollsAroundInput{
            {"@..",
             ".@.",
             "..."},
            {0, 0},
            1},

        // Edge (not corner) -> 2
        GetRollsAroundInput{
            {"@@@",
             "...",
             "..."},
            {0, 1},
            2},

        // No rolls -> 0
        GetRollsAroundInput{
            {"...",
             "...",
             "..."},
            {1, 1},
            0}));


struct GetValidRollsInput
{
    GRID grid;
    int expected_valid;
};
class CorrectValidRollsTest
    : public ::testing::TestWithParam<GetValidRollsInput>
{
protected:
    std::unique_ptr<PDepartment> dept;
    GetValidRollsInput input;

    void SetUp() override
    {
        input = GetParam();
        dept = std::make_unique<PDepartment>(input.grid);
    }
};

TEST_P(CorrectValidRollsTest, ValidateValidRollsInGrid)
{
    EXPECT_EQ(dept->get_valid_rolls_index_in_grid().size(), input.expected_valid);
}


INSTANTIATE_TEST_SUITE_P(
    AccessibleRolls,
    CorrectValidRollsTest,
    ::testing::Values(
        GetValidRollsInput{
            {
                {'.','.','@','@','.','@','@','@','@','.'},
                {'@','@','@','.','@','.','@','.','@','@'},
                {'@','@','@','@','@','.','@','.','@','@'},
                {'@','.','@','@','@','@','.','.','@','.'},
                {'@','@','.','@','@','@','@','.','@','@'},
                {'.','@','@','@','@','@','@','@','.','@'},
                {'.','@','.','@','.','@','.','@','@','@'},
                {'@','.','@','@','@','.','@','@','@','@'},
                {'.','@','@','@','@','@','@','@','@','.'},
                {'@','.','@','.','@','@','@','.','@','.'}
            },
            13
        }
    )
);

