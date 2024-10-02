// Normally sort the array using heapsort
// But at the same time trace the minimum difference every time examine_min_diff
//  (equivalent to textbook's extract-min) routine is called, and update it if
//  neccessary.
// Finally when sort is completed, all differences is checked and
//  we simply return it.

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <vector>
size_t pq_parent(size_t i) { return i / 2; }
size_t pq_young_child(size_t i) { return i * 2; }
size_t pq_top() { return 1; }
size_t pq_len(size_t x) { return x - 1; }
void pq_swap(std::vector<int>& q, size_t i1, size_t i2) {
    auto t{q[i1]};
    q[i1] = q[i2];
    q[i2] = t;
}
void bubble_down(std::vector<int>& q, size_t p) {
    auto c{pq_young_child(p)};
    auto min_idx{p};
    for (size_t i = 0; i < 2; i++) {
        if (c + i <= pq_len(q.size()) && q[c + i] < q[min_idx]) min_idx = c + i;
    }
    if (min_idx == p) return;
    // swap
    pq_swap(q, p, min_idx);
    // recurse
    bubble_down(q, min_idx);
}
std::vector<int> make_heap(const std::vector<int>& v) {
    std::vector<int> q(v.size() + 1);
    std::copy(v.cbegin(), v.cend(), q.begin() + 1);

    for (size_t i = pq_len(q.size()) / 2; i >= 1; i--) {
        bubble_down(q, i);
    }
    return q;
}
int examine_min_diff(std::vector<int>& q) {
    if (pq_len(q.size()) <= 0) throw std::invalid_argument{"Empty queue"};
    if (pq_young_child(pq_top()) <= pq_len(q.size())) {
        auto dm{std::min(q[pq_young_child(pq_top())] - q[pq_top()],
                         q[pq_young_child(pq_top()) + 1] - q[pq_top()])};
        q[pq_top()] = q[pq_len(q.size())];
        q.resize(q.size() - 1);
        bubble_down(q, pq_top());
        return dm;
    } else {
        return std::numeric_limits<int>::max();
    }
}
int find_min_diff(const std::vector<int>& v) {
    std::vector<int> q{make_heap(v)};
    auto min_diff{std::numeric_limits<int>::max()};
    for (size_t i = 0; i < v.size() - 1; i++) {
        min_diff = std::min(min_diff, examine_min_diff(q));
    }
    return min_diff;
}
int main(int argc, char const* argv[]) {
    assert(find_min_diff({-4, -1, 1, 4, 7}) == 2);
    assert(find_min_diff({6, 3, 2, 1}) == 1);
    assert(find_min_diff({124, 63, 23, 78, 11, 52}) == 11);
    return 0;
}
