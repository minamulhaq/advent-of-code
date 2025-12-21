
#include "cafeteria.hpp"

Cafeteria::Cafeteria(/* args */)
{
}

Cafeteria::~Cafeteria()
{
}

ID_RANGES Cafeteria::sort_id_ranges(ID_RANGES &id_ranges)
{
    sort(id_ranges.begin(), id_ranges.end(), [](ID_RANGE x, ID_RANGE y)
         { return x.first < y.first; });
    return id_ranges;
}

bool Cafeteria::verify_id(const ID &id, const ID_RANGES &ids)
{
    for (auto range : ids)
    {
        if ((range.first <= id) && (id <= range.second))
        {
            for (auto i = range.first; i <= range.second; i++)
            {
                total.insert(i);
            }
            return true;
        }
    }
    return false;
}

long long Cafeteria::get_total_fresh(void)
{
    return total.size();
}

MERGED_RANGES Cafeteria::merge_ranges_in_deque(const ID_RANGES &id_ranges)
{
    MERGED_RANGES merged;
    if (id_ranges.empty())
        return merged;

    ID_RANGES sorted = id_ranges;
    sort_id_ranges(sorted);

    merged.emplace_back(sorted[0]);

    for (size_t i = 1; i < sorted.size(); ++i)
    {
        auto &last = merged.back();
        const auto &cur = sorted[i];

        // overlap OR touching
        if (cur.first <= last.second + 1)
        {
            last.second = std::max(last.second, cur.second);
        }
        else
        {
            merged.emplace_back(cur);
        }
    }

    return merged;
}

long long Cafeteria::count_fresh(const ID_RANGES &id_ranges)
{
    auto merged_ranges = merge_ranges_in_deque(id_ranges);

    long long fresh = 0;
    for (auto mr : merged_ranges)
    {
        fresh += (mr.second - mr.first + 1);
    }
    return fresh;
}
