/*
    Same strategy as exercise 4-13.

    Sort left endpoints and right endpoints by its coordinate,
        giving each element a score along the way.
        Left endpoint:+1
        Right endpoint:-1
    Calc the partial sum of new array above and trace the interval
    in which the point p resides in most intervals, this is, partial
    sum is largest

    Return all the intervals which match the conditions of the statement.
*/

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

struct Interval {
    int cd_left;
    int cd_right;
    friend bool operator==(const Interval& itv1, const Interval& itv2) {
        return itv1.cd_left == itv2.cd_left && itv1.cd_right == itv2.cd_right;
    }
};

std::vector<Interval> get_max_overlaps(const std::vector<Interval>& itvs) {
    enum InvEnds { stt = 1, end = -1 };
    std::vector<std::pair<int, InvEnds>> labeled_ends;
    // parse
    for (const auto& itv : itvs) {
        labeled_ends.push_back({itv.cd_left, InvEnds::stt});
        labeled_ends.push_back({itv.cd_right, InvEnds::end});
    }
    // sort
    std::sort(labeled_ends.begin(), labeled_ends.end(),
              [](const auto& a, const auto& b) {
                  if (a.first != b.first) return a.first < b.first;
                  return a.second > b.second;
              });
    // traverse
    int overlap_cnt{0};
    int overlap_max{0};
    std::vector<Interval> traced;
    for (auto it{labeled_ends.cbegin()}; it != labeled_ends.cend(); ++it) {
        if (it->second == InvEnds::end) {
            if (overlap_max < overlap_cnt) {
                overlap_max = overlap_cnt;
                traced.clear();
                traced.push_back({(it - 1)->first, it->first});
            } else if (overlap_cnt == overlap_max) {
                traced.push_back({(it - 1)->first, it->first});
            }
        }
        overlap_cnt += static_cast<int>(it->second);
    }
    return traced;
}

int main(int argc, char const* argv[]) {
    assert(get_max_overlaps({Interval{-3, 3}, Interval{5, 15}}) ==
           (std::vector{Interval{-3, 3}, Interval{5, 15}}));
    assert(get_max_overlaps({Interval{-3, 5}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 5}}));
    assert(get_max_overlaps({Interval{-3, 8}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 8}}));
    assert(get_max_overlaps({Interval{5, 5}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 5}}));
    assert(get_max_overlaps({Interval{10, 15}, Interval{5, 15}}) ==
           (std::vector{Interval{10, 15}}));
    assert(get_max_overlaps({Interval{10, 17}, Interval{5, 15}}) ==
           (std::vector{Interval{10, 15}}));
    assert(get_max_overlaps({Interval{15, 17}, Interval{5, 15}}) ==
           (std::vector{Interval{15, 15}}));

    assert(get_max_overlaps({Interval{1, 3}, Interval{2, 6}, Interval{8, 10},
                             Interval{7, 18}}) ==
           (std::vector{Interval{2, 3}, Interval{8, 10}}));
    assert(get_max_overlaps({Interval{10, 40}, Interval{20, 60},
                             Interval{50, 90}, Interval{15, 70}}) ==
           (std::vector{Interval{20, 40}, Interval{50, 60}}));

    return 0;
}
