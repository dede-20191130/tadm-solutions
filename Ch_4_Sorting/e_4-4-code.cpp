// FIrst, traverse input array, and classify each color and save them.
// Next, sort the array using saved data, in order that is all reds before all
//  blues before all yellows.

//  Complexity: n(first traversal)+n(each stored color array traversal) = Θ(n)

#include <algorithm>
#include <array>
#include <cassert>
#include <utility>
#include <vector>
enum class Color { red, blue, yellow };
constexpr auto operator+(Color a) noexcept {
    return static_cast<std::underlying_type_t<Color>>(a);
}

using colored_ints = std::vector<std::pair<int, Color>>;

void sort_colored_int_array(colored_ints& ci_s) {
    std::array<std::vector<int>, +Color::yellow + 1> store_each_clr{};
    for (const auto& ci : ci_s) {
        store_each_clr[+ci.second].push_back(ci.first);
    }
    size_t idx{0};
    for (size_t j = 0; j < store_each_clr.size(); j++) {
        for (auto&& v_ci : store_each_clr[j]) {
            ci_s[idx++] = {v_ci, static_cast<Color>(j)};
        }
    }
}

int main(int argc, char const* argv[]) {
    colored_ints ci_s{{1, Color::blue}};
    sort_colored_int_array(ci_s);
    assert(ci_s == (colored_ints{{1, Color::blue}}));
    ci_s = {{2, Color::red}};
    sort_colored_int_array(ci_s);
    assert(ci_s == (colored_ints{{2, Color::red}}));
    ci_s = {{4, Color::yellow}};
    sort_colored_int_array(ci_s);
    assert(ci_s == (colored_ints{{4, Color::yellow}}));

    ci_s = {{1, Color::yellow}, {2, Color::yellow}};
    sort_colored_int_array(ci_s);
    assert(ci_s == (colored_ints{{1, Color::yellow}, {2, Color::yellow}}));

    ci_s = {{1, Color::blue},
            {3, Color::red},
            {4, Color::blue},
            {6, Color::yellow},
            {9, Color::red}};
    sort_colored_int_array(ci_s);
    assert(ci_s == (colored_ints{
                       {3, Color::red},
                       {9, Color::red},
                       {1, Color::blue},
                       {4, Color::blue},
                       {6, Color::yellow},
                   }));
    return 0;
}
