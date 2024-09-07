#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
class Segment_tree {
   protected:
    std::vector<T> t;
    size_t n;
    virtual T make_elem(const int i) const = 0;
    virtual T make_base_elem() const = 0;
    virtual T combine(T a, T b) const = 0;
    constexpr size_t i_root() const { return 1; }
    constexpr size_t i_left_child(size_t i) const { return 2 * i; }
    constexpr size_t i_right_child(size_t i) const { return 2 * i + 1; }

   public:
    Segment_tree() = delete;
    Segment_tree(const std::vector<int>& a) : n{a.size()} {
        t.resize(a.size() * 3);
    };
    virtual ~Segment_tree() = default;
    void build(const std::vector<int>& a, size_t pos, size_t tl, size_t tr) {
        if (tl == tr) {
            t[pos] = make_elem(a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, i_left_child(pos), tl, tm);
            build(a, i_right_child(pos), tm + 1, tr);
            t[pos] = combine(t[i_left_child(pos)], t[i_right_child(pos)]);
        }
    }
    T query(size_t l, size_t r) const {
        const auto helper{[&](auto helper, size_t pos, size_t tl, size_t tr,
                              size_t l, size_t r) -> T {
            if (l > r) return make_base_elem();
            if (l == tl && r == tr) return t[pos];
            size_t tm = (tl + tr) / 2;
            return combine(
                helper(helper, i_left_child(pos), tl, tm, l, std::min(r, tm)),
                helper(helper, i_right_child(pos), tm + 1, tr,
                       std::max(l, tm + 1), r));
        }};
        return helper(helper, i_root(), 0, n - 1, l, r);
    }
};

class Min_tree : public Segment_tree<int> {
   private:
    int make_elem(const int i) const override { return i; }
    int make_base_elem() const override {
        return std::numeric_limits<int>::max();
    }
    int combine(int a, int b) const { return std::min(a, b); }

   public:
    Min_tree(const std::vector<int>& a) : Segment_tree<int>(a) {
        build(a, i_root(), 0, n - 1);
    }
};

int main(int argc, char const* argv[]) {
    Min_tree seeker{{1}};
    assert(seeker.query(0, 0) == 1);

    seeker = {{1, 2}};
    assert(seeker.query(0, 0) == 1);
    assert(seeker.query(0, 1) == 1);
    assert(seeker.query(1, 1) == 2);
    seeker = {{2, 1}};
    assert(seeker.query(0, 0) == 2);
    assert(seeker.query(0, 1) == 1);
    assert(seeker.query(1, 1) == 1);

    seeker = {{30, 40, 10, 50, 80, 60, 20}};
    assert(seeker.query(0, 0) == 30);
    assert(seeker.query(0, 1) == 30);
    assert(seeker.query(0, 2) == 10);
    assert(seeker.query(0, 6) == 10);
    assert(seeker.query(1, 3) == 10);
    assert(seeker.query(2, 4) == 10);
    assert(seeker.query(3, 5) == 50);
    assert(seeker.query(4, 6) == 20);
    assert(seeker.query(3, 6) == 20);
    return 0;
}