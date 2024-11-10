// Use hash table to store the times of occurrence of each number
// Finally, traverse the hash table and find the largest times of occurrence

#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <vector>

int find_mode(const std::vector<int> v) {
    std::unordered_map<int, int> ht;
    for (auto&& e : v) {
        ht[e]++;
    }
    return std::max_element(
               ht.cbegin(), ht.cend(),
               [](auto& a, auto& b) { return a.second < b.second; })
        ->first;
}

int main(int argc, char const* argv[]) {
    assert(find_mode({{1}}) == 1);
    assert(find_mode({{1, 1, 2}}) == 1);
    assert(find_mode({{4, 6, 2, 4, 3, 1}}) == 4);
    assert(find_mode({{4, 6, 2, 4, 6, 6}}) == 6);
    assert(find_mode(
               {{7, 3, 8, 2, 1, 5, 2, 2, 3, 9, 6, 4, 2, 6, 8, 1, 2, 7}}) == 2);
    return 0;
}