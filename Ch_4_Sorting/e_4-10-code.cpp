// Subproblem-a: First sort the array, then use the same logic in subproblem-b.
// Subproblem-b: Find two numbers, one from smaller side and one from larger
//  side.
//  (1) Let r1 as the smallest number.
//  (2) Verify the number one by one from the largest number, let the number as
//      r2.
//      If r1+r2=x, return true.
//      Once r2 < x-r1, then verify r1 one by one from smaller to larger.
//  (3) If r1 overtakes r2, return false.

#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <vector>

bool is_sum_2_for_sorted(const std::vector<double>& v, double x) {
    auto i_l{0};
    for (auto i_u{v.size() - 1}; i_l < i_u;) {
        auto current{v[i_l] + v[i_u]};
        if (current == x)
            return true;
        else if (current < x)
            ++i_l;
        else
            --i_u;
    }
    return false;
}
bool is_sum_2(const std::unordered_set<double>& st, double x) {
    std::vector<double> v{st.cbegin(), st.cend()};
    std::sort(v.begin(), v.end());
    return is_sum_2_for_sorted(v, x);
}

int main(int argc, char const* argv[]) {
    // for subproblem a
    assert(is_sum_2({1.0, 2.0}, 3.0));
    assert(!is_sum_2({1.0, 2.0}, 4.0));
    std::unordered_set<double> st{1.3, 1.1, 0.4, 0.5, 0.6};
    assert(!is_sum_2(st, 2.0));
    assert(is_sum_2(st, 1.9));
    assert(is_sum_2(st, 1.0));
    assert(!is_sum_2(st, 1.2));
    // for subproblem b
    std::vector<double> v{1.5, 2.5, -0.2, -0.1, 1.3};
    std::sort(v.begin(), v.end());
    assert(!is_sum_2_for_sorted(v, 1.9));
    assert(is_sum_2_for_sorted(v, 2.3));
    assert(is_sum_2_for_sorted(v, 1.4));
    assert(!is_sum_2_for_sorted(v, 1.5));
    assert(is_sum_2_for_sorted(v, 4.0));
    assert(!is_sum_2_for_sorted(v, 3.0));

    return 0;
}
