#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

void sort_seq(vector<int>& v, int& cnt_comparison) {
    cnt_comparison = 0;
    int cnt_0{0};
    int cnt_1{0};

    // repeat while there are at least 2 elements to compare
    size_t ir_open{v.size()};
    int weight{1};
    for (; 1 < ir_open; weight <<= 1) {
        size_t new_iro{0};
        // traverse and do pairwise comparisons
        //// among the comparison, construct the new array for the next
        //// traversal
        for (size_t i = 0; i < ir_open - 1; i += 2) {
            ++cnt_comparison;
            if (v[i] == v[i + 1]) {
                v[new_iro++] = v[i];
            } else {
                cnt_0 += weight;
                cnt_1 += weight;
            }
        }
        if (ir_open & 1) {
            ++cnt_comparison;
            if (!v[ir_open - 1])
                cnt_0 += weight;
            else
                cnt_1 += weight;
        }
        ir_open = new_iro;
    }
    if (ir_open == 1) {
        ++cnt_comparison;
        if (!v[0])
            cnt_0 += weight;
        else
            cnt_1 += weight;
    }
    // reconstruct the array by the count of 0 and 1
    fill_n(v.begin(), cnt_0, 0);
    fill(v.begin() + cnt_0, v.end(), 1);
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
    assert(cnt_comparison == 6);
    v = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    sort_seq(v, cnt_comparison);
    assert(v == (vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert(cnt_comparison == 11);

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
