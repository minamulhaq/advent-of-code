
#ifndef __01_DIAL_ROTATOR_H_
#define __01_DIAL_ROTATOR_H_

#include <optional>
#include <string>

#define ROLL_OVER 100

class DialRotator {
   public:
    using ParseResult = std::optional<std::pair<char, int>>;

    DialRotator(int s);
    void rotate(const std::string& in);
    ParseResult parse_input(const std::string& input_str) const;

    int get_zero_count() const;
    int get_state() const;

   private:
    int current_state;
    int zero_count;
};

#endif  // __01_DIAL_ROTATOR_H_
