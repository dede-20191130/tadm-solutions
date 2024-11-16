// For simplicity, suppose all names follow name convention of
//  "First_name Last_name" (separated by one space)
// First, we distribute the names of cards into hash table
//  with hashing using two heading letter of first name and that of last name
// Then, sort each bucket and record distinct names in it.

// Complexity: O((n/(26**4)*log(n/(26**4)))*26**4)
//  = O(nlog(n/456976))
//  = O(nlogn)
//  The complexity is the same as the case if we don't distribute into buckets.
//  But the time required for sorting is smaller, so whole performance is
//      better.

#include <algorithm>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

constexpr char DELIM{' '};
vector<string> identify_distinct_names(const vector<string>& names) {
    unordered_map<string, vector<string>> buckets;
    for (const auto& nm : names) {
        auto p_dl{nm.find(DELIM)};
        string key{nm.substr(0, min((size_t)2, p_dl)) + nm.substr(p_dl + 1, 2)};
        buckets[key].push_back(nm);
    }

    vector<string> dist_nms;
    for (auto& [k, v] : buckets) {
        sort(v.begin(), v.end());
        string_view prev{""};
        for (const auto& nm : v) {
            if (nm != prev) {
                dist_nms.push_back(nm);
                prev = nm;
            }
        }
    }
    return dist_nms;
}

int main(int argc, char const* argv[]) {
    auto result{identify_distinct_names(
        {"Abb Cdd", "Abc Cdd", "Abb Cde", "Abb Cdd", "Abc Cdd", "Abc Cde",
         "Add Cbb", "Add Cbb", "Add Cbb", "Add Cbb", "Adc Cbe", "Adc Cbb",
         "Adc Cbe", "Adc Cbe", "Add Cbe", "Add Cbb", "Eff Ghh", "Eff Ghh",
         "Efi Ghh", "Efi Ghh", "Eff Ghj", "Eff Ghj", "Rff Ghh", "RRR KKK"})};
    assert(result.size() == 13);
    sort(result.begin(), result.end());
    assert(result[0] == "Abb Cdd");
    assert(result[1] == "Abb Cde");
    assert(result[2] == "Abc Cdd");
    assert(result[3] == "Abc Cde");
    assert(result[4] == "Adc Cbb");
    assert(result[5] == "Adc Cbe");
    assert(result[6] == "Add Cbb");
    assert(result[7] == "Add Cbe");
    assert(result[8] == "Eff Ghh");
    assert(result[9] == "Eff Ghj");
    assert(result[10] == "Efi Ghh");
    assert(result[11] == "RRR KKK");
    assert(result[12] == "Rff Ghh");

    return 0;
}
