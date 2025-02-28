#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

struct Pool {
    int val;
    size_t cnt{0};
};

void sort_seq(vector<int>& v, int& cnt_comparison) {
    cnt_comparison = 0;

    // examine data
    size_t cnt_zero{0};
    size_t cnt_one{0};
    Pool p;
    for (size_t i{0}; i < v.size() - 1; ++i) {
        if (!p.cnt) {
            p.val = v[i];
            p.cnt++;
        } else {
            ++cnt_comparison;
            if (p.val < v[i]) {
                cnt_zero += p.cnt;
                ++cnt_one;
                p.cnt = 0;
            } else if (v[i] < p.val) {
                ++cnt_zero;
                cnt_one += p.cnt;
                p.cnt = 0;
            } else
                p.cnt++;
        }
    }

    // clean pool
    if (p.cnt) {
        ++cnt_comparison;
        if (!p.val)
            cnt_zero += p.cnt;
        else
            cnt_one += p.cnt;
    }

    // reconstruct
    auto it{v.begin()};
    fill(it, it + cnt_zero, 0);
    it += cnt_zero;
    *it++ = v.back();
    fill(it, it + cnt_one, 1);
}

int main(int argc, char const* argv[]) {
    vector<int> v;
    int cnt_comparison;

    v = {0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0}));
    v = {1};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{1}));

    v = {0, 1};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 1}));
    v = {1, 0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 1}));

    v = {0, 0, 1};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 0, 1}));
    v = {0, 1, 0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 0, 1}));
    v = {1, 0, 0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 0, 1}));

    v = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}));
    assert(cnt_comparison == 5);
    v = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert(cnt_comparison == 10);

    v.resize(1000);
    auto it{v.begin()};
    fill(it, it + 500, 0);
    it += 500;
    fill(it, it + 500, 1);
    vector cp_v{v};
    random_shuffle(v.begin(), v.end());
    sort_seq(v, cnt_comparison);
    assert(v == cp_v);
    cout << "Comparison No1| Count: " << cnt_comparison
         << ", Propertion:" << (double)cnt_comparison / 1000 << endl;
    v.resize(10000);
    it = v.begin();
    fill(it, it + 5000, 0);
    it += 5000;
    fill(it, it + 5000, 1);
    cp_v = v;
    random_shuffle(v.begin(), v.end());
    sort_seq(v, cnt_comparison);
    assert(v == cp_v);
    cout << "Comparison No2| Count: " << cnt_comparison
         << ", Propertion:" << (double)cnt_comparison / 10000 << endl;

    return 0;
}
