#include "pdept.hpp"

static INDEXES directions{
    pair(-1, 0),
    pair(-1, 1),
    pair(0, 1),
    pair(1, 1),
    pair(1, 0),
    pair(1, -1),
    pair(0, -1),
    pair(-1, -1),
};

PDepartment::PDepartment(const GRID &grid) : _mGrid(grid)
{
    _mrows = _mGrid.size();
    _mcols = _mGrid.at(0).size();
}

PDepartment::~PDepartment()
{
}

int PDepartment::rows(void)
{
    return _mrows;
}

int PDepartment::cols(void)
{
    return _mcols;
}

bool PDepartment::is_roll(const int &row, const int &col)
{
    if (!is_valid({row, col}))
        return false;
    return _mGrid[row][col] == '@';
}

INDEXES PDepartment::get_neighbours(const INDEX &current)
{
    INDEXES n;
    for (auto d : directions)
    {
        INDEX neighbour = pair(current.first + d.first, current.second + d.second);
        if (is_valid(neighbour) && (neighbour != current))
        {
            n.emplace_back(neighbour);
        }
    }
    return n;
}

int PDepartment::get_roll_around_index(const INDEX &index)
{
    int count = 0;

    INDEXES neighbours = get_neighbours(index);
    for (auto n : neighbours)
    {
        if (is_roll(n.first, n.second))
        {
            count++;
        }
    }
    return count;
}

bool PDepartment::is_valid(const INDEX &n)
{
    return n.first >= 0 && n.first < _mrows &&
           n.second >= 0 && n.second < _mcols;
}

vector<INDEX> PDepartment::get_valid_rolls_index_in_grid()
{
    vector<INDEX> valid{};

    for (int row = 0; row < _mrows; ++row)
    {
        for (int col = 0; col < _mcols; ++col)
        {
            INDEX idx{row, col};

            if (!is_roll(idx.first, idx.second))
                continue;

            if (get_roll_around_index(idx) < 4)
                valid.emplace_back(idx);
        }
    }

    return valid;
}

int PDepartment::remove_rolls(void)
{
    int total_removed = 0;
    while (true)
    {
        auto indexes = get_valid_rolls_index_in_grid();
        if (indexes.empty())
        {
            break;
        }
        total_removed += remove_selected_rolls(indexes);
    };

    return total_removed;
}

int PDepartment::remove_selected_rolls(const INDEXES &indexes)
{
    int removed = 0;
    for (auto idx : indexes)
    {
        _mGrid.at(idx.first).at(idx.second) = 'x';
        removed++;
    }
    return removed;
}
