// Combine set A and B into new array C (not 'set')
// Sort C such that duplicate value can be detected quickly
// Remove duplicates and create new set

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

std::unordered_set<int> create_union(const std::unordered_set<int>& s1,
                                     const std::unordered_set<int>& s2) {
    std::vector<int> v_comb{s1.cbegin(), s1.cend()};
    v_comb.insert(v_comb.end(), s2.cbegin(), s2.cend());

    std::sort(v_comb.begin(), v_comb.end());

    auto it_last{std::unique(v_comb.begin(), v_comb.end())};
    v_comb.erase(it_last, v_comb.end());
    return {v_comb.cbegin(), v_comb.cend()};
}

int main(int argc, char const* argv[]) {
    assert(create_union({1}, {1}) == (std::unordered_set<int>{1}));
    assert(create_union({1}, {2}) == (std::unordered_set<int>{1, 2}));
    assert(create_union({1, 2, 3}, {4, 5, 6}) ==
           (std::unordered_set<int>{1, 2, 3, 4, 5, 6}));
    assert(create_union({1, 2, 2, 3, 3}, {4, 5, 6}) ==
           (std::unordered_set<int>{1, 2, 3, 4, 5, 6}));
    assert(create_union({1, 2, 2, 3, 3}, {2, 3, 4}) ==
           (std::unordered_set<int>{1, 2, 3, 4}));
    assert(create_union({1, 2, 2, 3, 3}, {3, 3, 2, 2, 1}) ==
           (std::unordered_set<int>{1, 2, 3}));
    return 0;
}
