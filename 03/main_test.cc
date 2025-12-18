#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>

#include "gtest/gtest.h"
#include "joltage.hpp"
using namespace std;

struct VoltageTestCase {
    std::string input;
    std::vector<int> expected;
    long long max_joltage;
};

// FIX: Change inheritance to TestWithParam while keeping your class name
class JoltageTest : public ::testing::TestWithParam<VoltageTestCase> {
   protected:
    std::unique_ptr<Joltage> jol;
    void SetUp() override { jol = std::make_unique<Joltage>(); }
};

INSTANTIATE_TEST_SUITE_P(
    VoltageParsingSuite, JoltageTest,
    ::testing::Values(
        VoltageTestCase{"987654321111111",
                        {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1},
                        987654321111},

        VoltageTestCase{"811111111111119",
                        {8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9},
                        811111111119},
        VoltageTestCase{"234234234234278",
                        {2, 3, 4, 2, 3, 4, 2, 3, 4, 2, 3, 4, 2, 7, 8},
                        434234234278},

        VoltageTestCase{"818181911112111",
                        {8, 1, 8, 1, 8, 1, 9, 1, 1, 1, 1, 2, 1, 1, 1},
                        888911112111}

                    ));

TEST_P(JoltageTest, CorrectlyParsesVariousInputs) {
    const auto& param = GetParam();
    std::vector<int> result = jol->parse_voltages_from_line(param.input);
    ASSERT_EQ(result.size(), param.expected.size())
        << "Failed on input: " << param.input;
    EXPECT_EQ(result, param.expected) << "Failed on input: " << param.input;
}

TEST_P(JoltageTest, CorrectlyComputeMaxJoltage) {
    const auto& param = GetParam();
    auto vec_in = param.expected;
    long long max = jol->get_max_joltage_for_one_line(vec_in);
    ASSERT_EQ(max, param.max_joltage);
}