#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template <typename T>
void reverse(std::vector<T>& v, const size_t i, const size_t j) {
    auto it{v.begin()};
    std::reverse(it + i, it + j + 1);
}

size_t partition_helper(std::vector<int>& v, const size_t i_l, const size_t i_r,
                        const int pvt) {
    // if length==1, judge position-x from how large the value is than pivot
    if (i_r == i_l) {
        if (pvt <= v[i_l])
            return i_l;
        else
            return i_l + 1;
    }

    auto i_mid{(i_l + i_r) / 2};
    auto pos_x_l{partition_helper(v, i_l, i_mid, pvt)};
    auto pos_x_r{partition_helper(v, i_mid + 1, i_r, pvt)};

    // merge two position-x
    if (i_mid < pos_x_l)
        return pos_x_r;
    else if (i_mid + 1 == pos_x_r)
        return pos_x_l;
    else {
        auto dist_r{pos_x_r - i_mid - 1};
        reverse(v, pos_x_l, pos_x_r - 1);
        return pos_x_l + dist_r;
    }
}

void sort_helper(std::vector<int>& v, const size_t i_l, const size_t i_r) {
    // if left index isn't 'left' to right index, exit
    if (i_r <= i_l) return;

    auto firsthigh{partition_helper(v, i_l, i_r - 1, v[i_r])};
    reverse(v, firsthigh, i_r);

    // recurse sortiong for two subarrays
    if (0 < firsthigh) sort_helper(v, i_l, firsthigh - 1);
    sort_helper(v, firsthigh + 1, i_r);
}

// For test (not randomize)
void suor(std::vector<int>& v) { sort_helper(v, 0, v.size() - 1); }

void sort_using_only_reverse(std::vector<int>& v) {
    std::random_shuffle(v.begin(), v.end());
    sort_helper(v, 0, v.size() - 1);
}

// **** For comparison (performance measurement) ***********************
// O(n^2) sortiong algorithm
void insertion_sort(std::vector<int>& v) {
    for (size_t i{0}; i < v.size(); i++) {
        for (size_t j{i}; j > 0 && v[j] < v[j - 1]; --j) {
            auto tmp{v[j]};
            v[j] = v[j - 1];
            v[j - 1] = tmp;
        }
    }
}
// For measurement
template <std::regular_invocable<> Func>
void measure_time(std::ostream& out, Func func, std::string_view target_name) {
    auto start{std::chrono::high_resolution_clock::now()};
    auto erapsed{
        [&]() { return std::chrono::high_resolution_clock::now() - start; }};

    auto get_micro_ticks{[](const std::chrono::nanoseconds& d) {
        return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
    }};

    func();

    out << "Erapsed time for " << target_name << ":"
        << get_micro_ticks(erapsed()) << std::endl;
}
// ************************************************************************************

int main(int argc, char const* argv[]) {
    std::vector<int> v{1};
    suor(v);
    assert(v == (std::vector{1}));

    v = {1, 2};
    suor(v);
    assert(v == (std::vector{1, 2}));
    v = {2, 1};
    suor(v);
    assert(v == (std::vector{1, 2}));

    v = {1, 2, 3};
    suor(v);
    assert(v == (std::vector{1, 2, 3}));
    v = {1, 3, 2};
    suor(v);
    assert(v == (std::vector{1, 2, 3}));
    v = {2, 1, 3};
    suor(v);
    assert(v == (std::vector{1, 2, 3}));
    v = {2, 3, 1};
    suor(v);
    assert(v == (std::vector{1, 2, 3}));
    v = {3, 1, 2};
    suor(v);
    assert(v == (std::vector{1, 2, 3}));
    v = {3, 2, 1};
    suor(v);
    assert(v == (std::vector{1, 2, 3}));

    v = {7, 3, 8, 2, 4, 5, 6, 1};
    suor(v);
    assert(v == (std::vector{1, 2, 3, 4, 5, 6, 7, 8}));

    v = {22, 17, 5, 4,  13, 7,  9,  21, 19, 10, 1, 8, 11,
         12, 2,  3, 25, 24, 16, 20, 15, 23, 14, 6, 18};
    suor(v);
    assert(v == (std::vector{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                             14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}));

    v = {13, 23, 18, 2, 12, 16, 15, 20, 3,  8,  19, 14, 21,
         25, 6,  4,  9, 10, 17, 1,  5,  24, 11, 22, 7};
    suor(v);
    assert(v == (std::vector{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                             14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}));

    // mass test
    std::vector<int> v_mass(1000);
    std::iota(v_mass.begin(), v_mass.end(), -500);
    std::vector<int> cp_v(v_mass);
    for (auto i{0}; i < 10; ++i) {
        sort_using_only_reverse(cp_v);
        assert(cp_v == v_mass);
    }

    // performance measurement
    v_mass.resize(40000);
    std::iota(v_mass.begin(), v_mass.end(), 1);
    measure_time(
        std::cout,
        [&]() {
            std::random_shuffle(v_mass.begin(), v_mass.end());
            insertion_sort(v_mass);
        },
        "Insertion sort");
    measure_time(
        std::cout, [&]() { sort_using_only_reverse(v_mass); },
        "Sort using reverse operation");
    return 0;
}
