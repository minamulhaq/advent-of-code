#ifndef _03_JOLTAGE_HPP__
#define _03_JOLTAGE_HPP__

#include <vector>
#include <string>
using namespace std;

using ALL_LINES = vector<string>;

class Joltage {
   private:
    long long total_voltage;

   public:
    Joltage(void);
    void parse_voltages_from_line(const string& s);
    long long get_max_joltage_for_one_line(const vector<int>& in);
    long long get_total_joltage(void);
    ~Joltage();
};

#endif  // _03_JOLTAGE_HPP__
