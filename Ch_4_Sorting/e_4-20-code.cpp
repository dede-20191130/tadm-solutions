#include <algorithm>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <vector>
size_t pq_parent(const size_t i) { return i / 2; }
size_t pq_young_child(const size_t i) { return i * 2; }
size_t pq_top() { return 1; }
size_t pq_len(const size_t x) { return x - 1; }
int pq_compare(const std::vector<int>& q, const size_t i_parent,
               const std::function<int(const int, const int)> comp) {
    auto i_chd{pq_young_child(i_parent)};
    if (pq_len(q.size()) < i_chd + 1) return q[i_chd];
    return comp(q[i_chd], q[i_chd + 1]);
}
void pq_swap(std::vector<int>& q, const size_t i1, const size_t i2) {
    auto t{q[i1]};
    q[i1] = q[i2];
    q[i2] = t;
}
void bubble_down_limited_descents(std::vector<int>& q, const size_t p,
                                  const size_t cnt, const size_t limit) {
    if (cnt == limit) return;
    auto c{pq_young_child(p)};
    auto min_idx{p};
    for (size_t i = 0; i < 2; i++) {
        if (c + i <= pq_len(q.size()) && q[c + i] > q[min_idx]) min_idx = c + i;
    }
    if (min_idx == p) return;
    // swap
    pq_swap(q, p, min_idx);
    // recurse
    bubble_down_limited_descents(q, min_idx, cnt + 1, limit);
}
std::vector<int> make_heap_limited_descents(const std::vector<int>& v,
                                            const size_t limit) {
    std::vector<int> q(v.size() + 1);
    std::copy(v.cbegin(), v.cend(), q.begin() + 1);

    for (size_t i = pq_len(q.size()) / 2; i >= 1; i--) {
        bubble_down_limited_descents(q, i, 0, limit);
    }
    return q;
}

auto f_int_max{[](const int a, const int b) { return std::max(a, b); }};

int get_second_largest(const std::vector<int>& v) {
    auto q{make_heap_limited_descents(v, 2)};
    if (pq_len(q.size()) < 2) throw std::invalid_argument{"Elements shortage"};
    return pq_compare(q, pq_top(), f_int_max);
}

int get_third_largest(const std::vector<int>& v) {
    auto q{make_heap_limited_descents(v, 3)};
    if (pq_len(q.size()) < 3) throw std::invalid_argument{"Elements shortage"};
    auto i_chd{pq_young_child(pq_top())};
    struct S_idx {
        size_t i_lrg;
        size_t i_sml;
    };
    S_idx s_idx{q[i_chd] > q[i_chd + 1] ? S_idx{i_chd, i_chd + 1}
                                        : S_idx{i_chd + 1, i_chd}};

    if (pq_len(q.size()) < pq_young_child(s_idx.i_lrg)) return q[s_idx.i_sml];
    return std::max(q[s_idx.i_sml], pq_compare(q, s_idx.i_lrg, f_int_max));
}

int main(int argc, char const* argv[]) {
    assert(get_second_largest({2, 5}) == 2);
    assert(get_second_largest({6, 2, 5, -3}) == 5);
    assert(get_second_largest(
               {-4, -43, -51, -8, 1, 15, 18, 2, 3, 37, 6, 7, 8, 99}) == 37);
    assert(get_second_largest(
               {-4, -43, -51, -8, 1, 15, 18, 2, 3, -37, 6, 7, 8, 99}) == 18);

    assert(get_third_largest({2, 5, -3}) == -3);
    assert(get_third_largest({6, 2, 5, -3}) == 2);
    assert(get_third_largest(
               {-4, -43, -51, -8, 1, 15, 18, 2, 3, 37, 6, 7, 8, 99}) == 18);
    assert(get_third_largest(
               {-4, -43, -51, -8, 1, 15, 18, 2, 3, -37, 6, 7, 8, 99}) == 15);
    return 0;
}
