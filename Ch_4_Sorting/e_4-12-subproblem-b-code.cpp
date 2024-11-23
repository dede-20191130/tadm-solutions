// Use the same procedure as used in merge logic in mergesort
//  - Pick smallest element from one of the top of sorted arrays
//      and repeat this until one of them becomes empty
//  - Ignore duplicate values in merging
#include <algorithm>
#include <cassert>
#include <vector>

std::vector<int> create_union(const std::vector<int>& v1,
                              const std::vector<int>& v2) {
    std::vector<int> result;
    auto it_v1{v1.cbegin()};
    auto it_v2{v2.cbegin()};
    while (it_v1 != v1.cend() && it_v2 != v2.cend()) {
        if (*it_v1 < *it_v2) {
            if (result.empty() || result.back() != *it_v1)
                result.push_back(*it_v1);
            ++it_v1;
        } else {
            if (result.empty() || result.back() != *it_v2)
                result.push_back(*it_v2);
            ++it_v2;
        }
    }
    if (it_v1 != v1.cend()) {
        if (result.back() == *it_v1) ++it_v1;
        result.insert(result.end(), it_v1, v1.cend());
    }
    if (it_v2 != v2.cend()) {
        if (result.back() == *it_v2) ++it_v2;
        result.insert(result.end(), it_v2, v2.cend());
    }
    return result;
}

// For check an array sorted and unique
std::vector<int> checked_sorted_unique(const std::vector<int>& v) {
    std::vector<int> cp_v{v};
    std::sort(cp_v.begin(), cp_v.end());
    auto it_last{std::unique(cp_v.begin(), cp_v.end())};
    cp_v.erase(it_last, cp_v.end());
    assert(v == cp_v);
    return v;
}

int main(int argc, char const* argv[]) {
    assert(create_union(checked_sorted_unique({1}),
                        checked_sorted_unique({1})) == (std::vector<int>{1}));
    assert(
        create_union(checked_sorted_unique({1}), checked_sorted_unique({2})) ==
        (std::vector<int>{1, 2}));

    assert(create_union(checked_sorted_unique({1, 2, 5, 6}),
                        checked_sorted_unique({1, 2, 5, 6})) ==
           (std::vector<int>{1, 2, 5, 6}));
    assert(create_union(checked_sorted_unique({1, 2, 3}),
                        checked_sorted_unique({4, 5, 6})) ==
           (std::vector<int>{1, 2, 3, 4, 5, 6}));
    assert(create_union(checked_sorted_unique({1, 2, 3, 4}),
                        checked_sorted_unique({3, 4, 5, 6})) ==
           (std::vector<int>{1, 2, 3, 4, 5, 6}));
    assert(create_union(checked_sorted_unique({1, 5, 10, 15}),
                        checked_sorted_unique({2, 4, 6, 8, 10, 12, 14, 16})) ==
           (std::vector<int>{1, 2, 4, 5, 6, 8, 10, 12, 14, 15, 16}));
    return 0;
}
