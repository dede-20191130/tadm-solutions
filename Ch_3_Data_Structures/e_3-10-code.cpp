#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <string>

// I assume the letter is all in lowercase alphabet 26 letters
// time complexity: O(n)
bool check_anagram(std::string_view s1, std::string_view s2) {
    // if the length of both is different, return false
    if (s1.size() != s2.size()) return false;

    std::array<int, 26> char_count{};
    char_count.fill(0);
    // traverse s1 and record the occurence score
    //  of a charactor in a array
    std::ranges::for_each(
        s1, [&char_count](char c) { char_count[std::tolower(c) - 'a']++; });
    // traverse s2
    //  if there is a charactor not found in the array, return false
    //  decrement the occurence store of the charactor
    for (auto &&c : s2) {
        auto cc{std::tolower(c)};
        if (!char_count[cc - 'a']) return false;
        --char_count[cc - 'a'];
    }

    // traverse the array and check if the score is all 0
    // if and only if that is true, return true
    for (auto &&c_cnt : char_count) {
        if (c_cnt) return false;
    }
    return true;
}

int main(int argc, char const *argv[]) {
    assert(check_anagram("", ""));
    assert(check_anagram("a", "a"));
    assert(!check_anagram("aaabbb", "aaaaaa"));
    assert(!check_anagram("aaaaaa", "aaabbb"));
    assert(check_anagram("aaabbb", "bababa"));
    assert(check_anagram("silent", "listen"));
    assert(check_anagram("incest", "insect"));
    assert(!check_anagram("incest", "insert"));
    assert(!check_anagram("incest", "inssect"));
    return 0;
}
