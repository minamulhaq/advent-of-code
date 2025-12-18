
#include "joltage.hpp"

#include <algorithm>
#include <deque>
#include <iostream>
using namespace std;

Joltage::~Joltage() {}

void Joltage::parse_voltages_from_line(const string &s)
{
    vector<int> voltages;
    voltages.reserve(s.size());

    for (auto c : s)
    {
        if (isdigit(static_cast<unsigned char>(c)))
        {
            voltages.emplace_back(c - '0');
        }
    }
    long long maxnum = get_max_joltage_for_one_line(voltages);
    total_voltage += maxnum;
}

long long Joltage::get_total_joltage(void)
{
    return total_voltage;
}

Joltage::Joltage() : total_voltage(0) {}
long long Joltage::get_max_joltage_for_one_line(const vector<int> &in)
{
    const size_t TARGET_SIZE = 12;

    // 1. Corrected constraint check
    if (in.size() < TARGET_SIZE)
    {
        return 0;
    }

    int batteries_to_remove = static_cast<int>(in.size() - TARGET_SIZE);
    deque<int> stack;

    // 2. Monotonic Stack Logic
    for (int digit : in)
    {
        while (!stack.empty() && batteries_to_remove > 0 && digit > stack.back())
        {
            stack.pop_back();
            batteries_to_remove--;
        }
        stack.push_back(digit);
    }

    // 3. Ensure exactly 12 digits (handles non-decreasing edge cases)
    while (stack.size() > TARGET_SIZE)
    {
        stack.pop_back();
    }

    // 4. Optimized Left-to-Right conversion to long long
    long long result = 0;
    for (int digit : stack)
    {
        result = (result * 10) + digit;
    }

    return result;
}
