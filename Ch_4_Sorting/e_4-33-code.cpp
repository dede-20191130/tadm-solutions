/*
Construct binary search tree in which each node has the integer and
count nunber what times the integer appears in the array.

The height of the tree is O(logk) and counting one element of the array
takes O(logk) time.

After all counting, reconstruct the array based on the data in the tree.

Time complexity: O(n)*O(logk)=O(nlogk)
*/
#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

void sort(std::vector<int>& v) {
    std::map<int, int> tree;
    // store data
    for (const auto n : v) {
        ++tree[n];
    }
    // reconstruct
    auto it{v.begin()};
    for (const auto& [n, cnt] : tree) {
        std::fill(it, it + cnt, n);
        it += cnt;
    }
}

int main(int argc, char const* argv[]) {
    std::vector v{1};
    sort(v);
    assert(v == (std::vector<int>{1}));

    v = {2, 1};
    sort(v);
    assert(v == (std::vector<int>{1, 2}));

    v = {1, 2, 2};
    sort(v);
    assert(v == (std::vector<int>{1, 2, 2}));
    v = {2, 1, 2};
    sort(v);
    assert(v == (std::vector<int>{1, 2, 2}));
    v = {2, 2, 1};
    sort(v);
    assert(v == (std::vector<int>{1, 2, 2}));

    v = {3, 3, 2, 1, 4, 2, 1, 2, 2, 4, 3, 4, 3, 4, 4,
         3, 4, 4, 3, 2, 1, 4, 2, 3, 2, 4, 4, 2, 2, 3};
    sort(v);
    assert(v ==
           (std::vector<int>{1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
                             3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}));

    return 0;
}
