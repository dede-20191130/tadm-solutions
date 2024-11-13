// First, sort the array in descending order.
// Then, exanime from the head of the array
//  whether the value of index i is greater than i.
//  If not so, stop and return i-1.
// Repeat it until the end of the array.

#include <algorithm>
#include <cassert>
#include <vector>

int find_h_index(const std::vector<int>& citation_cnts) {
    std::vector<int> cp_cc(citation_cnts);
    std::sort(cp_cc.begin(), cp_cc.end(),
              [](auto& a, auto& b) { return a > b; });
    for (int i = 1; i <= static_cast<int>(cp_cc.size()); i++) {
        if (cp_cc[i - 1] < i) return i - 1;
    }
    return static_cast<int>(cp_cc.size());
}

int main(int argc, char const* argv[]) {
    assert(find_h_index({1}) == 1);
    assert(find_h_index({0}) == 0);
    assert(find_h_index({1, 1, 1, 1, 1, 1}) == 1);
    assert(find_h_index({6, 3, 9, 1, 3, 8}) == 3);
    assert(find_h_index({6, 3, 9, 1, 6, 8}) == 4);
    assert(find_h_index({9, 9, 9, 9, 9, 9}) == 6);
    assert(find_h_index({15, 33, 20, 30, 4, 5, 6, 7}) == 6);
    return 0;
}
