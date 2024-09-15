// Storing sum-of-left-room tree strategy

#include <cassert>
#include <vector>
struct roomnode {
    bool availability{true};
    int sum_of_left_room{0};
};

class Hotel_room_allotter {
   private:
    std::vector<roomnode> availables;
    constexpr static int i_root(const int l, const int r) {
        return (l + r) / 2;
    }
    constexpr static int av2num(bool av) { return static_cast<int>(av); }

    int build(int l, int r) {
        if (r < l) return 0;
        if (l == r) return 1;
        auto pos{i_root(l, r)};
        availables[pos].sum_of_left_room = build(l, pos - 1);
        return availables[pos].sum_of_left_room + 1 + build(pos + 1, r);
    }

   public:
    Hotel_room_allotter(int _n) : availables(_n) { build(0, _n - 1); }
    int partial_sum(int i) const {
        if (i < 0) return 0;

        int total_cnt{0};
        int l{0};
        int r{static_cast<int>(availables.size()) - 1};
        while (l <= r) {
            auto pos{i_root(l, r)};
            if (i < pos)
                r = pos - 1;
            else if (i == pos) {
                total_cnt += availables[pos].sum_of_left_room +
                             av2num(availables[pos].availability);
                break;
            } else {
                total_cnt += availables[pos].sum_of_left_room +
                             av2num(availables[pos].availability);
                l = pos + 1;
            }
        }
        return total_cnt;
    }
    int count(int l, int h) const {
        return partial_sum(h) - partial_sum(l - 1);
    }
    int checkin(int l, int h) {
        int tl{0};
        int tr{static_cast<int>(availables.size()) - 1};
        std::vector<roomnode *> nodes_in_the_way;
        while (true) {
            auto tm{i_root(tl, tr)};
            if (l < tm && availables[tm].sum_of_left_room) {
                nodes_in_the_way.push_back(&availables[tm]);
                tr = tm - 1;
            } else if (l <= tm && tm <= h && availables[tm].availability) {
                tl = tm;
                break;
            } else if (tm < h) {
                tl = tm + 1;
            } else
                return -1;
        }
        availables[tl].availability = !availables[tl].availability;
        for (auto nd : nodes_in_the_way) --nd->sum_of_left_room;
        return tl;
    }

    bool checkout(int x) {
        int tl{0};
        int tr{static_cast<int>(availables.size()) - 1};
        std::vector<roomnode *> nodes_in_the_way;
        int tm;
        while ((tm = i_root(tl, tr)) != x) {
            if (x < tm) {
                nodes_in_the_way.push_back(&availables[tm]);
                tr = tm - 1;
            } else {
                tl = tm + 1;
            }
        }
        if (availables[x].availability)
            return false;
        else {
            availables[x].availability = !availables[x].availability;
            for (auto nd : nodes_in_the_way) ++nd->sum_of_left_room;
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Hotel_room_allotter ha{1};
    assert(ha.count(0, 0) == 1);
    assert(ha.checkin(0, 0) == 0);
    assert(ha.checkin(0, 0) == -1);
    assert(ha.count(0, 0) == 0);
    assert(ha.checkout(0));
    assert(ha.count(0, 0) == 1);
    assert(!ha.checkout(0));
    assert(ha.count(0, 0) == 1);

    ha = (2);
    assert(ha.count(0, 0) == 1);
    assert(ha.count(1, 1) == 1);
    assert(ha.count(0, 1) == 2);
    assert(ha.checkin(0, 0) == 0);
    assert(ha.count(0, 0) == 0);
    assert(ha.count(0, 1) == 1);
    assert(ha.checkout(0));
    assert(ha.count(0, 0) == 1);
    assert(ha.count(0, 1) == 2);
    assert(ha.checkin(1, 1) == 1);
    assert(ha.count(0, 1) == 1);
    assert(ha.count(1, 1) == 0);
    assert(ha.checkout(1));
    assert(ha.count(0, 1) == 2);
    assert(ha.count(1, 1) == 1);
    assert(ha.checkin(0, 1) == 0);
    assert(ha.count(0, 1) == 1);
    assert(ha.checkin(0, 1) == 1);
    assert(ha.count(0, 1) == 0);
    assert(ha.checkout(0));
    assert(ha.checkin(1, 1) == -1);
    assert(ha.count(0, 1) == 1);

    ha = (5);
    assert(ha.checkin(0, 2) == 0);
    assert(ha.count(0, 4) == 4);
    assert(ha.checkin(0, 2) == 1);
    assert(ha.count(0, 4) == 3);
    assert(ha.checkin(0, 2) == 2);
    assert(ha.count(0, 4) == 2);

    assert(ha.checkin(0, 2) == -1);
    assert(ha.count(0, 4) == 2);

    assert(ha.checkin(0, 4) == 3);
    assert(ha.count(0, 4) == 1);
    assert(ha.checkin(0, 4) == 4);
    assert(ha.count(0, 4) == 0);

    assert(ha.checkout(0));
    assert(ha.count(0, 4) == 1);
    assert(!ha.checkout(0));
    assert(ha.count(0, 4) == 1);
    assert(ha.checkout(1));
    assert(ha.count(0, 4) == 2);
    assert(ha.checkout(2));
    assert(ha.count(0, 4) == 3);
    assert(ha.checkout(3));
    assert(ha.count(0, 4) == 4);
    assert(ha.checkout(4));
    assert(ha.count(0, 4) == 5);

    ha = (8);
    assert(ha.count(0, 7) == 8);
    assert(ha.count(1, 5) == 5);
    assert(ha.count(2, 6) == 5);

    assert(ha.checkin(1, 3) == 1);
    assert(ha.count(1, 5) == 4);
    assert(ha.checkin(2, 4) == 2);
    assert(ha.count(1, 5) == 3);

    assert(ha.checkout(1));
    assert(ha.count(1, 5) == 4);
    assert(ha.checkout(2));
    assert(ha.count(1, 5) == 5);
    assert(ha.checkin(7, 7) == 7);
    assert(ha.count(0, 7) == 7);
    assert(ha.checkin(7, 7) == -1);
    assert(ha.count(0, 7) == 7);

    ha = (13);
    assert(ha.count(11, 11) == 1);
    assert(ha.count(12, 12) == 1);

    ha = (264);
    assert(ha.count(0, 63) == 64);
    assert(ha.count(55, 222) == 168);
    assert(ha.count(128, 263) == 136);

    return 0;
}
