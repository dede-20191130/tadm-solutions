/*
Precondition: input array must not have duplicate value,
otherwise occasionally wiggleness cannot be accomplished.

We partition the array using median value of the array as pivot.
Median in this context = floor((n-1)/2)-th value of the array
on zero based indexing

Here, we use special indexing system so that
all element of odd index (original) come after all elements of
even index (original).
Example: the order [e0, e1, e2, e3, e4] gets converted
to [e0, e2, e4, e1, e3].

After partitioning, the last element of even index (original) is
median and all elements of even index is less than or equal to
median, while all elements of odd index is greater than median.

Time complexity: O(n)
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

constexpr size_t sp_idx(const size_t i, const size_t len) {
    if (i < ((len + 1) >> 1)) return i * 2;
    return 2 * (i - ((len + 1) >> 1)) + 1;
}

void partition_by_kth_elem(std::vector<int>& v, const size_t i_l,
                           const size_t i_r, const size_t k) {
    // if the array contains only single element, exit
    if (i_l == i_r) return;

    // take the last element as a pivot and partition
    const auto len{v.size()};
    auto firsthigh{i_l};
    for (auto i{i_l}; i < i_r; ++i) {
        if (v[sp_idx(i, len)] < v[sp_idx(i_r, len)]) {
            std::swap(v[sp_idx(i, len)], v[sp_idx(firsthigh, len)]);
            ++firsthigh;
        }
    }
    std::swap(v[sp_idx(i_r, len)], v[sp_idx(firsthigh, len)]);

    if (k < firsthigh)
        partition_by_kth_elem(v, i_l, firsthigh - 1, k);
    else if (k > firsthigh)
        partition_by_kth_elem(v, firsthigh + 1, i_r, k);
}

void wiggle_sort(std::vector<int>& v) {
    std::random_shuffle(v.begin(), v.end());
    partition_by_kth_elem(v, 0, v.size() - 1, (v.size() - 1) / 2);
}

bool check_wiggled(const std::vector<int>& v) {
    for (auto i{0}; i < v.size(); ++i) {
        if (i & 1) {
            if (v[i] <= v[i - 1]) return false;
            if (i != v.size() - 1 && v[i] <= v[i + 1]) return false;
        } else {
            if (i != 0 && v[i - 1] < v[i]) return false;
            if (i != v.size() - 1 && v[i + 1] < v[i]) return false;
        }
    }
    return true;
}

void println(auto rem, auto const& v) {
    for (std::cout << rem; auto e : v) std::cout << e << ' ';
    std::cout << '\n';
}

int main(int argc, char const* argv[]) {
    std::vector v{1};
    wiggle_sort(v);
    println("Sort 1: v = ", v);
    assert(check_wiggled(v));

    v = {2, 1};
    wiggle_sort(v);
    println("Sort 2: v = ", v);
    assert(check_wiggled(v));

    v = {3, 2, 1};
    assert(!check_wiggled(v));
    wiggle_sort(v);
    println("Sort 3: v = ", v);
    assert(check_wiggled(v));

    v = {3, 2, 1, 4, 5, 6, 7, 8, 9};
    assert(!check_wiggled(v));
    wiggle_sort(v);
    println("Sort 4-1: v = ", v);
    assert(check_wiggled(v));

    v = {3, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    assert(!check_wiggled(v));
    wiggle_sort(v);
    println("Sort 4-2: v = ", v);
    assert(check_wiggled(v));

    return 0;
}
