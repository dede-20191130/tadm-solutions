/*
Precondition: input array must not have duplicate value,
otherwise occasionally wiggleness cannot be accomplished.

First we find median value of the array.
Median in this context = floor((n-1)/2)-th value of the array
on zero based indexing

Traverse the array to find the element x whose index is even and
whose value > median, and find the element y whose index is odd and
whose value <= median.
If both are found, swap x and y.

Time complexity: O(n)
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int quickselect_helper(std::vector<int>& v, const size_t i_l, const size_t i_r,
                       const size_t k) {
    // if the array contains only single element, return it
    if (i_l == i_r) return v[i_l];

    // take the last element as a pivot and partition
    auto firsthigh{i_l};
    for (auto i{i_l}; i < i_r; ++i) {
        if (v[i] < v[i_r]) {
            std::swap(v[i], v[firsthigh]);
            ++firsthigh;
        }
    }
    std::swap(v[i_r], v[firsthigh]);

    if (k < firsthigh)
        return quickselect_helper(v, i_l, firsthigh - 1, k);
    else if (k > firsthigh)
        return quickselect_helper(v, firsthigh + 1, i_r, k);
    else
        return v[k];
}

int find_median(std::vector<int>& v) {
    std::random_shuffle(v.begin(), v.end());
    return quickselect_helper(v, 0, v.size() - 1, (v.size() - 1) / 2);
}

void wiggle_sort(std::vector<int>& v) {
    if (v.size() < 2) return;

    auto median{find_median(v)};

    size_t i_ev{0};
    size_t i_od{1};
    while (true) {
        while (i_ev < v.size() && v[i_ev] <= median) i_ev += 2;
        while (i_od < v.size() && median < v[i_od]) i_od += 2;
        if (i_ev >= v.size() && i_od >= v.size()) break;
        std::swap(v[i_ev], v[i_od]);
    }
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
