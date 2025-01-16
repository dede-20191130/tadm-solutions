/*
Partition the array into 3 parts.
Red elements must be collected forward in the array, and
Blue ones to be backward in the array (similar to quicksort partitioning).

One traversal is enough to partition them (linear time complexity)
*/

#include <algorithm>
#include <cassert>
#include <vector>
enum Color { red, white, blue };

Color examine(const std::vector<Color>& v, const size_t i) { return v[i]; }
void swap(std::vector<Color>& v, const size_t i, const size_t j) {
    std::swap(v[i], v[j]);
}

void r_w_b_sort(std::vector<Color>& v) {
    size_t r_opn_bound{0};
    size_t b_opn_bound{v.size() - 1};
    for (auto i{0}; i <= b_opn_bound; ++i) {
        if (examine(v, i) == blue) {
            while (i < b_opn_bound && examine(v, b_opn_bound) == blue)
                b_opn_bound--;
            if (i < b_opn_bound) swap(v, i, b_opn_bound--);
        }
        if (examine(v, i) == red) {
            swap(v, i, r_opn_bound++);
        }
    }
}

int main(int argc, char const* argv[]) {
    std::vector<Color> v{red};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{red}));
    v = {white};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{white}));
    v = {blue};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{blue}));

    v = {red, white};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{red, white}));
    v = {white, red};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{red, white}));
    v = {white, blue};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{white, blue}));
    v = {blue, white};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{white, blue}));
    v = {red, blue};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{red, blue}));
    v = {blue, red};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{red, blue}));

    v = {blue,  blue,  red,   white, red,   red,   blue, red,
         blue,  white, red,   red,   white, red,   blue, blue,
         white, white, white, red,   red,   white, red};
    r_w_b_sort(v);
    assert(v == (std::vector<Color>{red,   red,   red,   red,   red,   red,
                                    red,   red,   red,   red,   white, white,
                                    white, white, white, white, white, blue,
                                    blue,  blue,  blue,  blue,  blue}));

    return 0;
}
