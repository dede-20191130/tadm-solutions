#include <cassert>
#include <memory>
class Constant_time_dictionary {
   private:
    std::unique_ptr<size_t[]> arr_n;
    std::unique_ptr<size_t[]> arr_m;
    size_t m;
    size_t total_count{0};

   public:
    Constant_time_dictionary(size_t n, size_t _m)
        : m{_m},
          arr_n{std::make_unique<size_t[]>(n)},
          arr_m{std::make_unique<size_t[]>(_m)} {}

    bool search(size_t x) const {
        if (total_count < 1) return false;

        x--;
        auto idx_m_for_x{(arr_n[x] - reinterpret_cast<size_t>(&arr_m[0])) /
                         sizeof(size_t)};
        if (idx_m_for_x < 0 || total_count <= idx_m_for_x) return false;
        if (arr_m[idx_m_for_x] != reinterpret_cast<size_t>(&arr_n[x]))
            return false;
        return true;
    }
    void insert(size_t x) {
        if (total_count == m) return;

        x--;
        arr_m[total_count] = reinterpret_cast<size_t>(&arr_n[x]);
        arr_n[x] = reinterpret_cast<size_t>(&arr_m[total_count]);
        total_count++;
    }
    void delete_num(size_t x) {
        if (total_count < 1) return;

        x--;
        auto idx_m_for_x{(arr_n[x] - reinterpret_cast<size_t>(&arr_m[0])) /
                         sizeof(size_t)};
        if (idx_m_for_x < 0 || total_count <= idx_m_for_x) return;
        if (arr_m[idx_m_for_x] != reinterpret_cast<size_t>(&arr_n[x])) return;

        auto idx_n_for_tobe_replaced{
            (arr_m[total_count - 1] - reinterpret_cast<size_t>(&arr_n[0])) /
            sizeof(size_t)};
        arr_n[idx_n_for_tobe_replaced] =
            reinterpret_cast<size_t>(&arr_m[idx_m_for_x]);
        arr_m[idx_m_for_x] = arr_m[total_count - 1];
        total_count--;
    }
};

int main(int argc, char const *argv[]) {
    Constant_time_dictionary ctd{1, 1};
    assert(!ctd.search(1));
    ctd.insert(1);
    assert(ctd.search(1));
    ctd.delete_num(1);
    assert(!ctd.search(1));

    ctd = {2, 1};
    ctd.insert(1);
    assert(ctd.search(1));
    assert(!ctd.search(2));
    ctd.insert(2);
    assert(ctd.search(1));
    assert(!ctd.search(2));
    ctd.delete_num(2);
    assert(ctd.search(1));
    assert(!ctd.search(2));
    ctd.delete_num(1);
    assert(!ctd.search(1));
    assert(!ctd.search(2));
    ctd.insert(2);
    assert(!ctd.search(1));
    assert(ctd.search(2));

    ctd = {10, 3};
    assert(!ctd.search(1));
    ctd.insert(1);
    assert(ctd.search(1));
    assert(!ctd.search(2));
    ctd.insert(2);
    assert(ctd.search(2));
    assert(!ctd.search(10));
    ctd.insert(10);
    assert(ctd.search(10));

    assert(!ctd.search(5));
    ctd.insert(5);
    assert(!ctd.search(5));

    ctd.delete_num(2);
    assert(!ctd.search(2));
    assert(ctd.search(1));
    assert(ctd.search(10));

    return 0;
}