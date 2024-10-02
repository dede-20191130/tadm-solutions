// (Ascendingly) sorted array has maximum value in its tail and minimum value in
//  its head
// So we simply pick the values and calc the diff
// That can be applied for descendingly sorted array

#include <algorithm>
#include <cassert>
#include <vector>

int find_max_diff(const std::vector<int>& sorted_v) {
    return std::abs(sorted_v.back() - sorted_v.front());
}

int main(int argc, char const* argv[]) {
    assert(find_max_diff({-4, -1, 1, 4, 7}) == 11);
    assert(find_max_diff({6, 3, 2, 1}) == 5);
    return 0;
}
