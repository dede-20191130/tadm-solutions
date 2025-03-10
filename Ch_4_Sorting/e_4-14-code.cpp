/*
    Sort the coordinates of endpoints with Labeling 'start' and 'end'.
        order: ascending for coordinate and the way 'start' ends are always
            precede to 'end' ends.

    Traverse the newly created array and record intervals.
        How to pick the ends of new interval:
            Select the start end.
            Count   +1 when encountering 'start' end
                    -1 when encountering 'end' end
            If counter becomes 0, Create new interval and continue to find
            another new intwerval.

*/
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

struct Interval {
    int cd_start;
    int cd_end;
    friend bool operator==(const Interval& itv1, const Interval& itv2) {
        return itv1.cd_start == itv2.cd_start && itv1.cd_end == itv2.cd_end;
    }
};

std::vector<Interval> merge_intervals(const std::vector<Interval>& itvs) {
    enum InvEnds { stt = 1, end = -1 };
    std::vector<std::pair<int, InvEnds>> labeled_ends;
    // parse
    for (const auto& itv : itvs) {
        labeled_ends.push_back({itv.cd_start, InvEnds::stt});
        labeled_ends.push_back({itv.cd_end, InvEnds::end});
    }
    // sort
    std::sort(labeled_ends.begin(), labeled_ends.end(),
              [](const auto& a, const auto& b) {
                  if (a.first != b.first) return a.first < b.first;
                  return a.second > b.second;
              });
    // traverse
    std::vector<Interval> merged;
    bool flaged = false;
    unsigned int cnt{0};
    int cd_start;
    for (auto it{labeled_ends.cbegin()}; it != labeled_ends.cend(); it++) {
        if (!flaged) {
            cd_start = it->first;
            flaged = true;
        }
        cnt += static_cast<int>(it->second);
        if (!cnt) {
            merged.push_back({cd_start, it->first});
            flaged = false;
        }
    }
    return merged;
}

int main(int argc, char const* argv[]) {
    assert(merge_intervals({Interval{-3, 3}, Interval{5, 15}}) ==
           (std::vector{Interval{-3, 3}, Interval{5, 15}}));
    assert(merge_intervals({Interval{-3, 5}, Interval{5, 15}}) ==
           (std::vector{Interval{-3, 15}}));
    assert(merge_intervals({Interval{-3, 8}, Interval{5, 15}}) ==
           (std::vector{Interval{-3, 15}}));
    assert(merge_intervals({Interval{5, 5}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 15}}));
    assert(merge_intervals({Interval{10, 15}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 15}}));
    assert(merge_intervals({Interval{10, 17}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 17}}));
    assert(merge_intervals({Interval{15, 17}, Interval{5, 15}}) ==
           (std::vector{Interval{5, 17}}));

    assert(merge_intervals({Interval{1, 3}, Interval{2, 6}, Interval{8, 10},
                            Interval{7, 18}}) ==
           (std::vector{Interval{1, 6}, Interval{7, 18}}));

    return 0;
}
