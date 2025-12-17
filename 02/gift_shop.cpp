
#include "gift_shop.hpp"

#include <cassert>
#include <iostream>

using namespace std;

GiftShop::GiftShop(void) : sum(0) {}

long long GiftShop::get_sum(void) { return sum; }

void GiftShop::accumulate(const long long& start, const long long& end) {
    for (unsigned long long i = start; i <= end; i++) {
        std::string n{std::to_string(i)};
        if (is_invalid(n)) {
            sum += i;
        }
    }
}

GiftShop::~GiftShop() {}
bool GiftShop::is_invalid(const std::string& num) {
    int n = num.length();
    if (n < 2) return false;

    // pi[i] is the length of the longest proper prefix
    // of num[0..i] that is also a suffix of num[0..i].
    std::vector<int> pi(n, 0);

    // O(n) construction of the Failure Function
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && num[i] != num[j]) {
            j = pi[j - 1];
        }
        if (num[i] == num[j]) {
            j++;
        }
        pi[i] = j;
    }

    int longest_border = pi[n - 1];
    int period_len = n - longest_border;

    // The string is a perfect repetition if:
    // 1. A border exists (longest_border > 0)
    // 2. The length is divisible by the candidate period
    if (longest_border > 0 && n % period_len == 0) {
        return true;
    }

    return false;
}