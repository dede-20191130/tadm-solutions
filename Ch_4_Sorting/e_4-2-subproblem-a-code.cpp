// Go through whole array and trace the maximum and minimum value
// Finally calc the maximum of difference using traced two values

#include <algorithm>
#include <cassert>
#include <vector>
int find_max_diff(const std::vector<int>& v) {
    int max{v[0]}, min{v[0]};
    for (auto&& e : v) {
        max = std::max(max, e);
        min = std::min(min, e);
    }
    return max - min;
}

int main(int argc, char const* argv[]) {
    assert(find_max_diff({1, 3, -1, 5, 0, 9}) == 10);  // test
    return 0;
}
