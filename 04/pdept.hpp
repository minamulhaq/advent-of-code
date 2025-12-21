#ifndef __04_PDEPT_H_
#define __04_PDEPT_H_
#include <vector>

using namespace std;

using GRID = vector<string>;
using INDEX = pair<int, int>;
using INDEXES = vector<INDEX>;

class PDepartment
{
private:
    GRID _mGrid;
    int _mrows;
    int _mcols;

protected:
public:
    PDepartment(const GRID &grid);
    ~PDepartment();
    int rows(void);
    int cols(void);
    bool is_roll(const int &row, const int &col);
    INDEXES get_neighbours(const INDEX &current);
    int get_roll_around_index(const INDEX &index);
    bool is_valid(const INDEX &n);
    vector<INDEX> get_valid_rolls_index_in_grid(void);
    int remove_rolls(void);
    int remove_selected_rolls(const INDEXES &indexes);
};

#endif // __04_PDEPT_H_
