#include "dial_rotator.hpp"
#include <cmath>
#include <iostream>
#include <sstream>

DialRotator::DialRotator(int s) : current_state(s), zero_count(0) {
    std::cout << "Starting dial at: " << current_state << std::endl;
}

void DialRotator::rotate(const std::string& in) {
    ParseResult p = parse_input(in);
    if (!p.has_value()) {
        // Handle parsing error if necessary
        return;
    }

    char direction = p->first;
    int total_distance = p->second;
    int zero_count_in_rotation = 0;

    if (direction == 'R') {
        // Right Rotation: The number of times '0' is passed is the number of
        // full 100-click segments covered, starting from the current_state.
        // Example: Start=50, D=60. (50+60)/100 = 1.1 -> floor(1.1) = 1 pass.
        // Example: Start=10, D=90. (10+90)/100 = 1.0 -> floor(1.0) = 1 pass.
        // Example: Start=10, D=89. (10+89)/100 = 0.99 -> floor(0.99) = 0
        // passes.
        zero_count_in_rotation = static_cast<int>(std::floor(
            (static_cast<double>(current_state) + total_distance) / ROLL_OVER));
    } else if (direction == 'L') {
        // Left Rotation: The number of times '0' is passed is the number of
        // full 100-click segments covered, starting from the next '0' in the
        // path. Distance to the first '0' leftwards (including the click at 0
        // itself). Example: Start=50, D=60. Dist to 0 is 50. (50+60-1)/100 =
        // 109/100 -> floor(1.09) = 1 pass. Example: Start=50, D=50. Dist to 0
        // is 50. (50+50-1)/100 = 99/100 -> floor(0.99) = 0 passes. (Lands on 0,
        // not passes) Example: Start=50, D=51. Dist to 0 is 50. (50+51-1)/100 =
        // 100/100 -> floor(1.0) = 1 pass.

        // Distance required to reach 0 moving left: current_state. (0 is at
        // current_state steps)
        int distance_to_first_zero =
            current_state == 0 ? ROLL_OVER : current_state;

        // The number of clicks that occur *after* the initial zero pass.
        // Total distance past the first zero is (total_distance -
        // distance_to_first_zero) Each 100 clicks after that is another pass.
        if (total_distance >= distance_to_first_zero) {
            // If the total distance is enough to reach or pass the first 0
            // The first pass is counted if D > D_0
            zero_count_in_rotation = 1;
            int remaining_distance = total_distance - distance_to_first_zero;
            // Add the full rollovers in the remaining distance
            zero_count_in_rotation += remaining_distance / ROLL_OVER;
        }
    }

    zero_count += zero_count_in_rotation;

    if (direction == 'R') {
        current_state = (current_state + total_distance) % ROLL_OVER;
    } else if (direction == 'L') {
        int effective_rotation = total_distance % ROLL_OVER;
        current_state = (current_state - effective_rotation);
        current_state = (current_state % ROLL_OVER + ROLL_OVER) % ROLL_OVER;
    }
}

int DialRotator::get_zero_count() const { return zero_count; }
int DialRotator::get_state() const { return current_state; }

DialRotator::ParseResult DialRotator::parse_input(
    const std::string& input_str) const {
    std::stringstream ss(input_str);
    char dir;
    int rot;
    if (ss >> dir >> rot) {
        if (ss.peek() == std::stringstream::traits_type::eof()) {
            return ParseResult{std::make_pair(dir, rot)};
        }
    }
    return std::nullopt;
}