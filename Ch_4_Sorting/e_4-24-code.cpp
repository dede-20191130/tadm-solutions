/*
Partition the array so that negative values can be moved to forward.
*/
#include <algorithm>
#include <cassert>
#include <vector>
void neg_forward(std::vector<int>& v) {
    size_t firstpos{0};
    for (auto i{0}; i < v.size(); i++) {
        if (v[i] < 0) {
            std::swap(v[i], v[firstpos++]);
        }
    }
}

int main(int argc, char const* argv[]) {
    std::vector<int> v{-1};
    neg_forward(v);
    assert(v == (std::vector{-1}));
    v = {0};
    neg_forward(v);
    assert(v == (std::vector{0}));
    v = {1};
    neg_forward(v);
    assert(v == (std::vector{1}));

    v = {-1, 1};
    neg_forward(v);
    assert(v == (std::vector{-1, 1}));
    v = {1, -1};
    neg_forward(v);
    assert(v == (std::vector{-1, 1}));

    v = {1, -1, 2, -2, 3};
    neg_forward(v);
    assert(v == (std::vector{-1, -2, 2, 1, 3}));

    v = {18, -7,  -15, -18, 5,  11, -19, -2, 11,  2,
         -8, -13, -2,  8,   17, 2,  14,  0,  -11, 19};
    neg_forward(v);
    for (auto i{0}; i <= 8; ++i) assert(v[i] < 0);
    for (auto i{9}; i < v.size(); ++i) assert(v[i] >= 0);

    return 0;
}
