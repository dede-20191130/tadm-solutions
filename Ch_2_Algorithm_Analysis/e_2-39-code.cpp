#include <vector>
int find_missing(const std::vector<int>& missing_array) {
    int n{(int)missing_array.size()};

    // calc sum of not-missing array using summation formula
    int desired_sum = (n + 1) * (n + 2) / 2;

    // sum one by one from the array
    // O(n)
    int current_sum{0};
    for (int i = 0; i < n; i++) {
        current_sum += missing_array[i];
    }

    return desired_sum - current_sum;
}

#include <cassert>
int main(int argc, char const* argv[]) {
    assert(find_missing({2, 3, 4, 5, 6}) == 1);
    assert(find_missing({1, 2, 4, 5, 6}) == 3);
    assert(find_missing({1, 2, 3, 4}) == 5);
    return 0;
}
