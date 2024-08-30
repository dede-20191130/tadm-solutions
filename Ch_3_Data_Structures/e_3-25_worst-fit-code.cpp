#include <set>
#include <stdexcept>
#include <vector>

#include "./worst-fit.h"
int bin_packing_worst_fit(std::vector<int> weights) {
    // construct the tree which accomodates the rest spaces of bins
    std::multiset<int> spaces{};
    for (int i = 0; i < weights.size(); ++i) {
        if (weights[i] < 0 || 1000 < weights[i])
            throw std::invalid_argument("invalid weight");
        // place the object of weight[i]
        //  into the largest space
        // if there are no space available, add a new bin
        auto it{spaces.rbegin()};
        if (it == spaces.rend() || *it < weights[i]) {
            spaces.insert(1000 - weights[i]);

        } else {
            int new_space{*it - weights[i]};
            spaces.erase(std::next(it).base());
            spaces.insert(new_space);
        }
    }
    return spaces.size();
}