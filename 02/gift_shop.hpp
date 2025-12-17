#ifndef __02_GIFT_SHOP_H_
#define __02_GIFT_SHOP_H_

#include <sstream>
#include <string>
#include <vector>

using namespace std;
class GiftShop
{
private:
    long long sum;
    // const std::vector<std::pair<long long, long long>> &ranges;

public:
    GiftShop(void);
    long long get_sum(void);
    void accumulate(const long long &start, const long long &end);
    bool is_invalid(const string& num);
    ~GiftShop();
};

#endif // __02_GIFT_SHOP_H_
