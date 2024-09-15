// Segment-tree strategy

#include <cassert>
#include <vector>
class Hotel_room_allotter {
   private:
    std::vector<int> availables;
    int n;
    constexpr static int get_i_l_chld(int i) { return 2 * i + 1; }
    constexpr static int get_i_r_chld(int i) { return 2 * i + 2; }

    void build(int i, int tl, int tr) {
        if (tl == tr) {
            availables[i] = 1;
            return;
        }
        auto tm{(tl + tr) / 2};
        auto i_l_chld{get_i_l_chld(i)};
        auto i_r_chld{get_i_r_chld(i)};
        build(i_l_chld, tl, tm);
        build(i_r_chld, tm + 1, tr);
        availables[i] = availables[i_l_chld] + availables[i_r_chld];
    }

   public:
    Hotel_room_allotter(int _n) : n{_n} {
        availables.resize(n * 3);
        build(0, 0, n - 1);
    }
    int count_helper(int i, int tl, int tr, int l, int h) const {
        if (h < l) return 0;
        if (tl == l && tr == h) return availables[i];
        auto tm{(tl + tr) / 2};
        auto i_l_chld{get_i_l_chld(i)};
        auto i_r_chld{get_i_r_chld(i)};
        return count_helper(i_l_chld, tl, tm, l, std::min(tm, h)) +
               count_helper(i_r_chld, tm + 1, tr, std::max(tm + 1, l), h);
    }
    int count(int l, int h) const { return count_helper(0, 0, n - 1, l, h); }
    int checkin(int l, int h) {
        int i{0};
        int tl{0};
        int tr{n - 1};
        std::vector<int *> nodes_in_the_way;
        while (tl != tr) {
            auto tm{(tl + tr) / 2};
            auto i_l_chld{get_i_l_chld(i)};
            auto i_r_chld{get_i_r_chld(i)};
            nodes_in_the_way.push_back(&availables[i]);
            if (l <= tm && availables[i_l_chld]) {
                i = i_l_chld;
                tr = tm;
                h = std::min(tm, h);
            } else if (tm < h && availables[i_r_chld]) {
                i = i_r_chld;
                tl = tm + 1;
                l = std::max(tm + 1, l);
            } else
                return -1;
        }
        if (availables[i]) {
            --availables[i];
            for (auto nd : nodes_in_the_way) --*nd;
            return tl;
        }
        return -1;
    }

    bool checkout(int x) {
        int i{0};
        int tl{0};
        int tr{n - 1};
        std::vector<int *> nodes_in_the_way;
        while (tl != tr) {
            auto tm{(tl + tr) / 2};
            auto i_l_chld{get_i_l_chld(i)};
            auto i_r_chld{get_i_r_chld(i)};
            nodes_in_the_way.push_back(&availables[i]);
            if (x <= tm) {
                i = i_l_chld;
                tr = tm;
            } else {
                i = i_r_chld;
                tl = tm + 1;
            }
        }
        if (availables[i])
            return false;
        else {
            availables[i] = 1;
            for (auto nd : nodes_in_the_way) ++*nd;
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
