// For already sorted array, we need no mutation and examine a diff between each
// adjacent pair, and return the smallest.

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>
int find_min_diff(const std::vector<int>& sorted_v) {
    auto min_diff{std::numeric_limits<int>::max()};
    for (size_t i = 0; i < sorted_v.size() - 1; i++) {
        min_diff = std::min(min_diff, sorted_v[i + 1] - sorted_v[i]);
    }
    return min_diff;
}
std::vector<int> sorted_array(const std::vector<int>& v) {
    std::vector<int> v2(v.cbegin(), v.cend());
    std::sort(v2.begin(), v2.end());
    return v2;
}
int main(int argc, char const* argv[]) {
    assert(find_min_diff(sorted_array({-4, -1, 1, 4, 7})) == 2);
    assert(find_min_diff(sorted_array({6, 3, 2, 1})) == 1);
    assert(find_min_diff(sorted_array({124, 63, 23, 78, 11, 52})) == 11);
    return 0;
}
