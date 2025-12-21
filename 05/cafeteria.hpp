#ifndef _05_CAFETERIA_HPP__
#define _05_CAFETERIA_HPP__

#include <utility>
#include <vector>
#include <set>
#include <deque>

using namespace std;

using ID_RANGE = pair<long long, long long>;
using ID_RANGES = vector<ID_RANGE>;
using MERGED_RANGES = deque<pair<long long, long long>>;
using ID = long long;
using IDS = vector<ID>;

class Cafeteria
{
private:
    set<long long> total;

public:
    Cafeteria(/* args */);
    ~Cafeteria();
    ID_RANGES sort_id_ranges(ID_RANGES &id_ranges);
    MERGED_RANGES merge_ranges_in_deque(const ID_RANGES &id_ranges);
    long long count_fresh(const ID_RANGES& id_ranges);
    bool verify_id(const ID &id, const ID_RANGES &ids);
    long long get_total_fresh(void);
};

#endif // _05_CAFETERIA_HPP__
