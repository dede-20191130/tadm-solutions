/*
    Sort by its coordinate of left endpoints.

    Traverse the sorted array:
        If the interval linked target left endpoint is more coverable than
        the candidate-of-next interval, set it as newly candidate-of-next
        interval

        If the currently focused interval ends before the target left endpoint,
        save it and assign the candidate-of-next interval into the focused
        interval

        If the candidate-of-next interval already covers to m, save it and
        return the dedicated array for saving intervals.

        If there's a gap between currently focused interval and newly found one,
        return the 'not found' indicator.


*/

#include <algorithm>
#include <cassert>
#include <vector>

struct Interval {
    int cd_left;
    int cd_right;
    friend bool operator==(const Interval& itv1, const Interval& itv2) {
        return itv1.cd_left == itv2.cd_left && itv1.cd_right == itv2.cd_right;
    }
};

struct s_pick_fewer_covers {
    bool not_found{false};
    std::vector<Interval> covers;
};

s_pick_fewer_covers pick_fewer_covers(const std::vector<Interval>& itvs,
                                      int m) {
    std::vector<Interval> cp_itvs{itvs};
    std::sort(cp_itvs.begin(), cp_itvs.end(), [](const auto& a, const auto& b) {
        return a.cd_left < b.cd_left;
    });

    s_pick_fewer_covers save;

    const Interval* curr_focus{&cp_itvs.front()};
    const Interval* cand_next{nullptr};

    if (curr_focus->cd_left != 0) {
        save.not_found = true;
        return save;
    } else if (m <= curr_focus->cd_right) {
        save.covers.push_back(*curr_focus);
        return save;
    }

    save.covers.push_back(*curr_focus);

    for (auto it{cp_itvs.cbegin() + 1}; it != cp_itvs.cend(); ++it) {
        if (curr_focus->cd_right < it->cd_left) {
            if (!cand_next || cand_next->cd_right < it->cd_left) {
                save.not_found = true;
                return save;
            }
            save.covers.push_back(*cand_next);
            curr_focus = cand_next;
            cand_next = nullptr;
        }
        if (!cand_next || cand_next->cd_right < it->cd_right) {
            cand_next = &(*it);
            if (m <= cand_next->cd_right) {
                save.covers.push_back(*cand_next);
                return save;
            }
        }
    }
    save.not_found = true;
    return save;
}

int main(int argc, char const* argv[]) {
    auto result{pick_fewer_covers({Interval{0, 10}}, 9)};
    assert(!result.not_found);
    assert(result.covers == (std::vector{Interval{0, 10}}));
    result = pick_fewer_covers({Interval{0, 10}}, 10);
    assert(!result.not_found);
    assert(result.covers == (std::vector{Interval{0, 10}}));
    result = pick_fewer_covers({Interval{0, 10}}, 11);
    assert(result.not_found);

    result = pick_fewer_covers({Interval{0, 10}, Interval{11, 15}}, 12);
    assert(result.not_found);
    result = pick_fewer_covers({Interval{0, 10}, Interval{9, 15}}, 12);
    assert(!result.not_found);
    assert(result.covers == (std::vector{Interval{0, 10}, Interval{9, 15}}));
    result = pick_fewer_covers({Interval{0, 10}, Interval{9, 15}}, 15);
    assert(!result.not_found);
    assert(result.covers == (std::vector{Interval{0, 10}, Interval{9, 15}}));
    result = pick_fewer_covers({Interval{0, 10}, Interval{9, 15}}, 16);
    assert(result.not_found);

    std::vector<Interval> v{{Interval{0, 40}, Interval{20, 60},
                             Interval{50, 90}, Interval{15, 70}}};
    result = pick_fewer_covers(v, 14);
    assert(!result.not_found);
    assert(result.covers == (std::vector{Interval{0, 40}}));
    result = pick_fewer_covers(v, 50);
    assert(!result.not_found);
    assert(result.covers == (std::vector{Interval{0, 40}, Interval{15, 70}}));
    result = pick_fewer_covers(v, 80);
    assert(!result.not_found);
    assert(result.covers ==
           (std::vector{Interval{0, 40}, Interval{15, 70}, Interval{50, 90}}));
    return 0;
}
