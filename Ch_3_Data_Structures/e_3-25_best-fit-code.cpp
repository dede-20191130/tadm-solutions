#include "./best-fit.h"

#include <set>
#include <stdexcept>
#include <vector>

int bin_packing_best_fit(std::vector<int> weights) {
    // construct the tree which accomodates the rest spaces of bins
    std::multiset<int> spaces{};  // unit in gram
    for (int i = 0; i < weights.size(); ++i) {
        if (weights[i] < 0 || 1000 < weights[i])
            throw std::invalid_argument("invalid weight");
        // place the object of weight[i]
        //  into the first space that is greater than or equal to the weight
        // if there are no such space, add a new bin
        auto it{spaces.lower_bound(weights[i])};
        if (it == spaces.end()) {
            spaces.insert(1000 - weights[i]);

        } else {
            int new_space{*it - weights[i]};
            spaces.erase(it);
            spaces.insert(new_space);
        }
    }
    return spaces.size();
}