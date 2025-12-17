#include "gtest/gtest.h"
#include <string>
#include <sstream>
#include <optional>
#include <utility>
#include "dial_rotator.hpp"

class DialRotatorTest : public ::testing::Test {
protected:
    void RunRotations(int start_state, const std::vector<std::string>& commands, int expected_state, int expected_count) {
        std::stringstream ss;
        std::streambuf* oldCout = std::cout.rdbuf(ss.rdbuf());

        DialRotator rotator{start_state};

        for (const auto& cmd : commands) {
            rotator.rotate(cmd);
        }

        std::cout.rdbuf(oldCout);

        ASSERT_EQ(rotator.get_state(), expected_state)
            << "Final State mismatch. Expected: " << expected_state << ", Got: " << rotator.get_state();
        ASSERT_EQ(rotator.get_zero_count(), expected_count)
            << "Zero Count mismatch. Expected: " << expected_count << ", Got: " << rotator.get_zero_count();
    }
};


TEST_F(DialRotatorTest, SimpleRightRotation) {
    // Start at 10, rotate R5 -> Should land at 15
    RunRotations(10, {"R5"}, 15, 0);
}

TEST_F(DialRotatorTest, SimpleLeftRotation) {
    // Start at 20, rotate L7 -> Should land at 13
    RunRotations(20, {"L7"}, 13, 0);
}

TEST_F(DialRotatorTest, RightWrapAround) {
    // Start at 95, rotate R10 -> Should land at 5 (95 + 10 = 105; 105 % 100 = 5)
    RunRotations(95, {"R10"}, 5, 1); // R10 passes 0 once
}

TEST_F(DialRotatorTest, LeftWrapAround) {
    // Start at 5, rotate L10 -> Should land at 95 (5 - 10 = -5; -5 % 100 = 95)
    RunRotations(5, {"L10"}, 95, 1); // L10 passes 0 once
}

// --- Test Suite 2: Zero Counting (Part Two Logic) ---

TEST_F(DialRotatorTest, ZeroCrossings_ExampleSequence) {
    // Start at 50. Expected passes: 6
    // L68 (50->82): Passes 0 once
    // L30 (82->52): 0 passes
    // R48 (52->0): Passes 0 once
    // L5 (0->95): 0 passes
    // R60 (95->55): Passes 0 once
    // L55 (55->0): Passes 0 once
    // L1 (0->99): 0 passes
    // L99 (99->0): Passes 0 once
    // R14 (0->14): 0 passes
    // L82 (14->32): Passes 0 once

    // Total: 6
    const std::vector<std::string> example = {
        "L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"
    };
    RunRotations(50, example, 32, 6);
}

TEST_F(DialRotatorTest, ZeroCrossings_MultipleRollovers) {
    // Start at 50, Rotate R1000.
    // (50 + 1000) / 100 = 10.5 -> Should pass 0 ten times. Lands on 50.
    RunRotations(50, {"R1000"}, 50, 10);
}

TEST_F(DialRotatorTest, LeftMultipleRollovers) {
    // Start at 10, Rotate L310.
    // Distance to first 0 is 10. Remaining distance 310 - 10 = 300. 300/100 = 3 full rollovers.
    // Total passes: 1 (initial) + 3 (rollovers) = 4. Lands on 10.
    RunRotations(10, {"L310"}, 0, 4);
}

TEST_F(DialRotatorTest, LandsExactlyOnZero) {
    // Start at 50, Rotate R50. Lands on 0. Count should be 1.
    RunRotations(50, {"R50"}, 0, 1);
}

TEST_F(DialRotatorTest, LandsExactlyOnZero_Rollaver) {
    // Start at 50, Rotate R150. Lands on 0. (50+150)/100 = 2.0. Count should be 2.
    RunRotations(50, {"R150"}, 0, 2);
}
