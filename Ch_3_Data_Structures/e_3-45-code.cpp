// Data structure is Hash Table (Hashmap)

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

template <typename T, typename U>
struct std::hash<std::pair<T, U>> {
    size_t operator()(const std::pair<T, U>& pr) const {
        return std::hash<T>()(pr.first) * std::hash<U>()(pr.second);
    }
};

void truncate_unalphabets(std::string& s) {
    auto it_bgn{std::find_if(s.cbegin(), s.cend(),
                             [](auto& c) { return std::isalpha(c); })};
    if (it_bgn == s.cend()) {
        s = "";
        return;
    }
    auto it_end{std::find_if(s.crbegin(), s.crend(),
                             [](auto& c) { return std::isalpha(c); })};
    s = std::string(it_bgn, it_end.base());
}

int main(int argc, char const* argv[]) {
    std::ifstream inf{"./sample-text2.txt"};
    if (!inf) {
        std::cerr << "cannot open file" << std::endl;
        return 1;
    }

    std::unordered_map<std::pair<std::string, std::string>, long> pair_store;

    std::string prev;
    inf >> prev;
    truncate_unalphabets(prev);

    std::string s;
    while (inf >> s) {
        truncate_unalphabets(s);
        if (prev.size() && s.size()) {
            pair_store[{prev, s}]++;
        }
        prev = s;
    }

    std::ofstream outf{"./count-result.txt"};
    if (!outf) {
        std::cerr << "cannot operate file" << std::endl;
        return 1;
    }

    std::vector<std::pair<long, std::pair<std::string, std::string>>>
        ordered_arr;
    std::transform(
        pair_store.cbegin(), pair_store.cend(), std::back_inserter(ordered_arr),
        [](auto& e) -> std::pair<long, std::pair<std::string, std::string>> {
            return {e.second, e.first};
        });
    std::sort(ordered_arr.begin(), ordered_arr.end(),
              [](auto& e1, auto& e2) { return e2.first < e1.first; });

    for (auto it{ordered_arr.cbegin()}; it != ordered_arr.cend(); it++) {
        outf << it->second.first << " " << it->second.second << ":" << it->first
             << "\n";
    }

    return 0;
}
