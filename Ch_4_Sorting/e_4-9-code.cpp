// First, sort the set
//  (As long as c++ concerns, additional sorting is not required for set, which
//      is already sorted natively.)

// Find the k numbers, each number is labeled as n-th number
//  in the order in which they were picked.
// The way to find is different according to 'n'

// For 1st number, pick the number from the range of index [0, n-1]
// For 2nd-(k-1)th number, pick the number from the range of index [a+1, n-1]
//  'a' denotes the index of the number picked for previous number
// For kth number, we can use binary search in the range of index [a+1, n-1] and
//  the complexity is log(n)

// The total complexity is:
//  O(n)*O(n^(k-2))*O(log(n)) = O(n^(k-1)log(n))

#include <cassert>
#include <cstddef>
#include <set>
#include <vector>

// definitions
bool can_add_up_helper_iterate(const std::vector<int>& v_s, int k, size_t lbnd,
                               int t);
bool can_add_up_helper_binary_search(const std::vector<int>& v_s, size_t lbnd,
                                     int t);

bool can_add_up(const std::set<int>& s, int k, int t) {
    std::vector<int> v_s{s.cbegin(), s.cend()};
    return can_add_up_helper_iterate(v_s, k, 0, t);
}
bool can_add_up_helper_iterate(const std::vector<int>& v_s, int k, size_t lbnd,
                               int t) {
    if (k == 1) return can_add_up_helper_binary_search(v_s, lbnd, t);
    auto ubnd_opn{v_s.size() - k + 1};
    for (size_t i = lbnd; i < ubnd_opn; i++) {
        auto new_t{t - v_s[i]};
        if (new_t < v_s[i + 1]) break;
        if (can_add_up_helper_iterate(v_s, k - 1, i + 1, new_t)) return true;
    }
    return false;
}
bool can_add_up_helper_binary_search(const std::vector<int>& v_s, size_t lbnd,
                                     int t) {
    for (auto ubnd{v_s.size() - 1}; lbnd <= ubnd;) {
        auto mid{(lbnd + ubnd) / 2};
        if (v_s[mid] < t)
            lbnd = mid + 1;
        else if (v_s[mid] == t)
            return true;
        else
            ubnd = mid - 1;
    }
    return false;
}

int main(int argc, char const* argv[]) {
    assert(can_add_up({1}, 1, 1));
    assert(!can_add_up({1}, 1, 2));

    assert(can_add_up({1, 5}, 1, 1));
    assert(can_add_up({1, 5}, 1, 5));
    assert(can_add_up({1, 5}, 2, 6));
    assert(!can_add_up({1, 5}, 2, 7));

    std::set<int> s{1, 2, 3, 10, 11, 12, 100, 101, 102};
    assert(can_add_up(s, 2, 3));
    assert(can_add_up(s, 2, 203));
    assert(can_add_up(s, 2, 14));
    assert(!can_add_up(s, 2, 26));
    assert(can_add_up(s, 3, 6));
    assert(!can_add_up(s, 4, 6));
    assert(can_add_up(s, 3, 33));
    assert(!can_add_up(s, 3, 34));
    assert(can_add_up(s, 4, 34));
    assert(can_add_up(s, 3, 24));
    assert(can_add_up(s, 4, 24));
    assert(!can_add_up(s, 5, 24));
    assert(can_add_up(s, 3, 204));
    assert(can_add_up(s, 3, 214));
    assert(can_add_up(s, 3, 303));
    assert(can_add_up(s, 8, 341));
    assert(!can_add_up(s, 8, 337));
    assert(can_add_up(s, 9, 342));
    return 0;
}
