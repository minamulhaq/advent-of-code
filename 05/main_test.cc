#include "gtest/gtest.h"
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include "cafeteria.hpp"

using namespace std;

struct SORT_ID_RANGES_INPUT
{
    ID_RANGES in;
    ID_RANGES expected;
};

class ID_RANGE_SORT_FIXTURE : public ::testing::TestWithParam<SORT_ID_RANGES_INPUT>
{
protected:
    unique_ptr<Cafeteria> _cafe;
    SORT_ID_RANGES_INPUT _input;
    void SetUp() override
    {
        _input = GetParam();
        _cafe = make_unique<Cafeteria>();
    }
    void TearDown() override {}
};

INSTANTIATE_TEST_SUITE_P(
    TEST_SUITE_ID_SORT,
    ID_RANGE_SORT_FIXTURE,
    ::testing::Values(
        SORT_ID_RANGES_INPUT{
            .in = {
                pair(3, 5),
                pair(10, 14),
                pair(16, 20),
                pair(12, 18)},
            .expected = {
                pair(3, 5),
                pair(10, 14),
                pair(12, 18),
                pair(16, 20),
            }}

        ));

TEST_P(ID_RANGE_SORT_FIXTURE, VerifyIDRangeSorting)
{
    ASSERT_EQ(_cafe->sort_id_ranges(_input.in), _input.expected);
}

struct MERGE_RANGES_INPUT
{
    ID_RANGES in;
    MERGED_RANGES expected;
};

class MERGED_RANGES_FIXTURE : public ::testing::TestWithParam<MERGE_RANGES_INPUT>
{
protected:
    unique_ptr<Cafeteria> _cafe;
    MERGE_RANGES_INPUT _input;
    void SetUp() override
    {
        _input = GetParam();
        _cafe = make_unique<Cafeteria>();
    }
    void TearDown() override {}
};

INSTANTIATE_TEST_SUITE_P(
    TEST_SUITE_MERGED_RANGES,
    MERGED_RANGES_FIXTURE,
    ::testing::Values(

        MERGE_RANGES_INPUT{
            .in = {
                pair(3, 5),
                pair(10, 14),
                pair(12, 18),
                pair(16, 20),
            },
            .expected = {
                pair(3, 5),
                pair(10, 20),
            }
        },

        // 1. No overlap
        MERGE_RANGES_INPUT{.in = {{1, 2}, {4, 5}, {7, 8}}, .expected = {{1, 2}, {4, 5}, {7, 8}}},

        // 2. Complete overlap
        MERGE_RANGES_INPUT{.in = {{1, 10}, {2, 3}, {4, 8}}, .expected = {{1, 10}}},

        // 3. Chain overlap
        MERGE_RANGES_INPUT{.in = {{1, 3}, {2, 5}, {4, 7}}, .expected = {{1, 7}}},

        // 4. Touching boundaries
        MERGE_RANGES_INPUT{.in = {{1, 3}, {4, 6}}, .expected = {{1, 6}}},

        // 5. Single element ranges
        MERGE_RANGES_INPUT{.in = {{5, 5}, {6, 6}, {7, 7}}, .expected = {{5, 7}}},

        // 6. Unsorted input
        MERGE_RANGES_INPUT{.in = {{10, 12}, {1, 3}, {4, 8}}, .expected = {{1, 8}, {10, 12}}},

        // 7. Duplicate ranges
        MERGE_RANGES_INPUT{.in = {{1, 5}, {1, 5}, {1, 5}}, .expected = {{1, 5}}},

        // 8. Large gaps
        MERGE_RANGES_INPUT{.in = {{1, 2}, {1000000, 1000001}}, .expected = {{1, 2}, {1000000, 1000001}}},

        // 9. Single range
        MERGE_RANGES_INPUT{.in = {{42, 99}}, .expected = {{42, 99}}},

        // 10. Empty input
        MERGE_RANGES_INPUT{.in = {}, .expected = {}}));

TEST_P(MERGED_RANGES_FIXTURE, VerifyIDRangeSorting)
{
    ASSERT_EQ(_cafe->merge_ranges_in_deque(_input.in), _input.expected);
}