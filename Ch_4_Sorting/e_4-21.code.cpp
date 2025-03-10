/*
We find (n/2)-th element as median value.

Find-k-th-element algorithm
    Select pivot and use partitioning algorithm of quicksort.
    Then extract k from the number of element
    in start-to-pivot or pivot-to-end according to the position relation between
    pivot and k.
    Repeat the algorithm until pivot's positon=k
*/

#include <algorithm>
#include <cassert>
#include <vector>

int qs_helper(std::vector<int>& v, const size_t i_l, const size_t i_r,
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
        return qs_helper(v, i_l, firsthigh - 1, k);
    else if (k > firsthigh)
        return qs_helper(v, firsthigh + 1, i_r, k);
    else
        return v[k];
}

int find_median(const std::vector<int>& v) {
    std::vector<int> cp_v{v};
    std::random_shuffle(cp_v.begin(), cp_v.end());
    return qs_helper(cp_v, 0, cp_v.size() - 1, cp_v.size() / 2);
}

int main(int argc, char const* argv[]) {
    assert(find_median({1}) == 1);
    assert(find_median({2, 1}) == 2);
    assert(find_median({6, -4, 8, -12, 7}) == 6);
    assert(find_median({4, 8, 6, -4, 8, -12, 7, 16, -11}) == 6);
    assert(find_median({2, 4, 8, 6, -4, 8, -12, 7, 16, -11}) == 6);
    assert(find_median({2, 4, 8, 6, -4, 8, -12, 7, 16, -11, -14}) == 4);
    assert(find_median({-20, -10, 2, 4, 8, 6, -4, 8, -12, 7, 16, -11, -14}) ==
           2);

    return 0;
}
