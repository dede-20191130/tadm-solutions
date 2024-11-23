#include <algorithm>
#include <cassert>
#include <vector>
struct More_thans {
    bool exist_mt_div2{false};
    bool exist_mt_div4{false};
    int mt_div2;
    int mt_div4;
};

More_thans find_mode_thans(const std::vector<int>& orig_v) {
    std::vector<int> v{orig_v};  // treat input as immutable

    More_thans result{};
    // get (n/2)-th element
    auto it_m{v.begin() + v.size() / 2};
    std::nth_element(v.begin(), it_m, v.end());
    auto v_m{*it_m};
    // move elements whose value is same as (n/2)-th element
    //  to the back of the array
    std::swap(v[v.size() / 2], v[v.size() - 1]);
    int bound{static_cast<int>(v.size() - 2)};
    while (0 <= bound && v[bound] == v_m) --bound;
    for (auto i{0}; i < bound; i++) {
        if (v[i] == v_m) {
            std::swap(v[i], v[bound]);
            while (0 <= bound && v[bound] == v_m) --bound;
        }
    }

    // check the existence of the number appearing more than n/2 times
    if ((v.size() - bound - 1) * 2 <= v.size()) return result;

    result.exist_mt_div2 = true;
    result.mt_div2 = v_m;

    // check if there is enough space for the number appearing more than n/4
    //  times
    if ((bound + 1) * 4 <= v.size()) return result;

    // get (n/2)-th element from the remaining part of array
    it_m = v.begin() + (bound + 1) / 2;
    std::nth_element(v.begin(), it_m, v.begin() + bound + 1);
    v_m = *it_m;

    // check the existence of the number appearing more than n/2 times
    //  in the remaining part of array
    int cnt{0};
    for (auto i{0}; i <= bound; i++) {
        if (v[i] == v_m) ++cnt;
    }
    if (cnt * 4 <= v.size()) return result;

    result.exist_mt_div4 = true;
    result.mt_div4 = v_m;
    return result;
}

int main(int argc, char const* argv[]) {
    auto mts{find_mode_thans({3, 1, 2, 3, 3, 2, 2, 3})};
    assert(!mts.exist_mt_div2);
    mts = find_mode_thans({1, 2, 4, 4, 4, 3, 4, 4, 2, 4, 3});
    assert(mts.exist_mt_div2 && mts.mt_div2 == 4 && !mts.exist_mt_div4);
    mts = find_mode_thans({1});
    assert(mts.exist_mt_div2 && mts.mt_div2 == 1 && !mts.exist_mt_div4);
    mts = find_mode_thans({1, 1, 1, 1, 1});
    assert(mts.exist_mt_div2 && mts.mt_div2 == 1 && !mts.exist_mt_div4);
    mts = find_mode_thans({1, 2});
    assert(!mts.exist_mt_div2);
    mts = find_mode_thans({2, 2, 1, 2, 2, 1, 2, 2, 2});
    assert(mts.exist_mt_div2 && mts.mt_div2 == 2 && !mts.exist_mt_div4);
    mts = find_mode_thans({4, 1, 2, 4, 4, 2, 4, 2, 4, 3, 4});
    assert(mts.exist_mt_div2 && mts.mt_div2 == 4 && mts.exist_mt_div4 &&
           mts.mt_div4 == 2);
    {
        std::vector<int> v{-2, -2, -2, 5, 5, 3, 3, 3, 3, 3, 3};

        for (auto i{0}; i < 10; i++) {
            std::random_shuffle(v.begin(), v.end());
            mts = find_mode_thans(v);
            assert(mts.exist_mt_div2 && mts.mt_div2 == 3 && mts.exist_mt_div4 &&
                   mts.mt_div4 == -2);
        }
    }
    return 0;
}
