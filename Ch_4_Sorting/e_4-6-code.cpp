// Sort the two set into two array 1,2
// Then traverse the array_1 from the smallest value to the largest,
//  at the same time array_2 from the largest value to the smallest.
// When two numbers cursored by each traversal is equal to x, save it.
// Do it until either array passes the last element.

// Complexity: 2O(nlogn)+O(2n)=O(nlogn)

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <utility>
#include <vector>

using pairs = std::vector<std::pair<int, int>>;

pairs find_pair_for(const std::unordered_set<int>& s1,
                    const std::unordered_set<int>& s2, int x) {
    std::vector<int> v1(s1.cbegin(), s1.cend());
    std::vector<int> v2(s2.cbegin(), s2.cend());
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    pairs prs;
    auto it_v1{v1.cbegin()};
    auto it_r_v2{v2.crbegin()};
    while (it_v1 != v1.cend() && it_r_v2 != v2.crend()) {
        auto sum_its{*it_v1 + *it_r_v2};
        if (sum_its <= x) {
            if (sum_its == x) prs.push_back({*it_v1, *it_r_v2});
            it_v1++;
        } else
            it_r_v2++;
    }
    return prs;
}

int main(int argc, char const* argv[]) {
    assert(find_pair_for({1}, {1}, 3) == (pairs{}));
    assert(find_pair_for({1}, {1}, 2) == (pairs{{1, 1}}));
    assert(find_pair_for({4, 3}, {3, 2}, 6) == (pairs{{3, 3}, {4, 2}}));
    assert(find_pair_for({17, 4, 11, 1, 25, 21}, {15, 3, 18, 2, 8, 20}, 29) ==
           (pairs{{11, 18}, {21, 8}}));
    return 0;
}
