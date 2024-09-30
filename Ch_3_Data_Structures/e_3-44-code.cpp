#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
class Segment_tree {
   protected:
    std::vector<T> t;
    size_t n;
    virtual T make_elem(int i) const = 0;
    virtual T make_base_elem() const = 0;
    virtual T combine(T a, T b) const = 0;

   public:
    Segment_tree() = delete;
    Segment_tree(const std::vector<int>& a) : n{a.size()} {
        t.resize(a.size() * 3);
    };
    virtual ~Segment_tree() = default;
    void build(const std::vector<int>& a, size_t v, size_t tl, size_t tr) {
        if (tl == tr) {
            t[v] = make_elem(a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = combine(t[v * 2], t[v * 2 + 1]);
        }
    }
    T query_helper(size_t v, size_t tl, size_t tr, size_t l, size_t r) const {
        if (l > r) return make_base_elem();
        if (l == tl && r == tr) return t[v];
        size_t tm = (tl + tr) / 2;
        return combine(
            query_helper(v * 2, tl, tm, l, std::min(r, tm)),
            query_helper(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
    }
    T query(size_t l, size_t r) const {
        return query_helper(1, 0, n - 1, l, r);
    }
};

class Product_tree : public Segment_tree<int> {
   private:
    int make_elem(int i) const override { return i; }
    int make_base_elem() const override { return 1; }
    int combine(int a, int b) const override { return a * b; }

   public:
    Product_tree(const std::vector<int>& a) : Segment_tree<int>(a) {
        build(a, 1, 0, n - 1);
    }
    auto product(size_t l, size_t r) const { return query(l, r); }
};

std::vector<int> create_M_array(const std::vector<int>& arr_x) {
    Product_tree pt{arr_x};
    std::vector<int> arr_m(arr_x.size());
    for (size_t i = 0; i < arr_m.size(); i++) {
        arr_m[i] = (0 < i ? pt.product(0, i - 1) : 1) *
                   pt.product(i + 1, arr_m.size() - 1);
    }
    return arr_m;
}

int main(int argc, char const* argv[]) {
    std::vector<int> base_arr_x{1};
    assert(create_M_array(base_arr_x) == (std::vector<int>{1}));

    base_arr_x = {10, 20};
    assert(create_M_array(base_arr_x) == (std::vector<int>{20, 10}));

    base_arr_x = {5, 3, 7};
    assert(create_M_array(base_arr_x) == (std::vector<int>{21, 35, 15}));

    base_arr_x = {5, 4, 3, 2, 6, 7, 8, 9};
    assert(create_M_array(base_arr_x) ==
           (std::vector<int>{72576, 90720, 120960, 181440, 60480, 51840, 45360,
                             40320}));

    return 0;
}
