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
    // traverse the array, and trace candidate and voting count status
    int cand{-1}, vo_cnt{0};
    size_t i_cand;
    for (auto i{0}; i <= v.size(); i++) {
        if (!vo_cnt) {
            cand = v[i];
            vo_cnt = 1;
            i_cand = i;
        } else {
            if (cand == v[i])
                ++vo_cnt;
            else
                --vo_cnt;
        }
    }

    // move elements whose value is same as candidate
    //  to the back of the array
    std::swap(v[i_cand], v[v.size() - 1]);
    int bound{static_cast<int>(v.size() - 2)};
    while (0 <= bound && v[bound] == cand) --bound;
    for (auto i{0}; i < bound; i++) {
        if (v[i] == cand) {
            std::swap(v[i], v[bound]);
            while (0 <= bound && v[bound] == cand) --bound;
        }
    }

    // check the existence of the number appearing more than n/2 times
    if ((v.size() - bound - 1) * 2 <= v.size()) return result;

    result.exist_mt_div2 = true;
    result.mt_div2 = cand;

    // check if there is enough space for the number appearing more than n/4
    //  times
    if ((bound + 1) * 4 <= v.size()) return result;
    // traverse the remaining part of array,
    //  and trace candidate and voting count status
    cand = 0;
    vo_cnt = 0;
    for (auto i{0}; i <= bound; i++) {
        if (!vo_cnt) {
            cand = v[i];
            vo_cnt = 1;
        } else {
            if (cand == v[i])
                ++vo_cnt;
            else
                --vo_cnt;
        }
    }

    // check the existence of the number appearing more than n/2 times
    //  in the remaining part of array
    int cnt{0};
    for (auto i{0}; i <= bound; i++) {
        if (v[i] == cand) ++cnt;
    }
    if (cnt * 4 <= v.size()) return result;

    result.exist_mt_div4 = true;
    result.mt_div4 = cand;
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
