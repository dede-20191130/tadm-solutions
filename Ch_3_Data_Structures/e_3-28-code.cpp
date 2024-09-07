#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

class Partial_sum {
   private:
    std::vector<double> range_sums;
    constexpr size_t i_root_of_range(size_t l, size_t r) const {
        return (l + r) / 2;
    }
    double build(const std::vector<double> &orig, size_t lb, size_t ub) {
        if (ub < lb) return 0;

        auto mid{i_root_of_range(lb, ub)};
        range_sums[mid] = orig[mid] + (mid > 0 ? build(orig, lb, mid - 1) : 0);

        return range_sums[mid] + build(orig, mid + 1, ub);
    }

   public:
    Partial_sum(std::initializer_list<double> lst) : range_sums(lst.size()) {
        std::vector<double> orig{lst};
        build(orig, 0, orig.size() - 1);
    }
    void add(size_t i, double y) {
        if (i < 0 || range_sums.size() <= i)
            throw std::invalid_argument("invalid_argument");

        size_t lb{0};
        size_t ub{range_sums.size() - 1};
        size_t mid;

        while ((mid = i_root_of_range(lb, ub)) != i) {
            if (i < mid) {
                range_sums[mid] += y;
                ub = mid - 1;
            } else
                lb = mid + 1;
        }
        range_sums[i] += y;
    }

    double query_partial_sum(size_t i) const {
        if (i < 0 || range_sums.size() <= i)
            throw std::invalid_argument("invalid_argument");

        double total_val{0};

        size_t lb{0};
        size_t ub{range_sums.size() - 1};
        size_t mid;

        while ((mid = i_root_of_range(lb, ub)) != i) {
            if (i < mid) {
                ub = mid - 1;
            } else {
                total_val += range_sums[mid];
                lb = mid + 1;
            }
        }

        return total_val + range_sums[i];
    }
};

int main(int argc, char const *argv[]) {
    Partial_sum ps{1};
    assert(ps.query_partial_sum(0) == 1);
    ps.add(0, 2);
    assert(ps.query_partial_sum(0) == 3);

    ps = {2, 3};
    assert(ps.query_partial_sum(0) == 2);
    assert(ps.query_partial_sum(1) == 5);
    ps.add(0, 4);
    assert(ps.query_partial_sum(0) == 6);
    assert(ps.query_partial_sum(1) == 9);
    ps.add(1, -4);
    assert(ps.query_partial_sum(0) == 6);
    assert(ps.query_partial_sum(1) == 5);

    ps = {1.5, 2.5, 3.1, 6.0, 4.2, 0.8, 8.5};
    assert(ps.query_partial_sum(0) == 1.5);
    assert(ps.query_partial_sum(2) == 7.1);
    assert(ps.query_partial_sum(3) == 13.1);
    assert(ps.query_partial_sum(4) == 17.3);
    assert(ps.query_partial_sum(6) == 26.6);
    ps.add(3, 4.0);
    assert(ps.query_partial_sum(2) == 7.1);
    assert(ps.query_partial_sum(3) == 17.1);
    assert(ps.query_partial_sum(4) == 21.3);
    return 0;
}
