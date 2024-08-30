#include <iostream>
#include <vector>

#include "../../../../util/random/random.h"
#include "../best-fit/best-fit.h"
#include "../worst-fit/worst-fit.h"

int main(int argc, char const *argv[]) {
    int best_fit_wins{0};
    int worst_fit_wins{0};
    int even{0};
    for (int i = 0; i < 10000; i++) {
        std::vector<int> v{};
        for (int j = 0; j < 100; j++) {
            v.push_back(Random::get(1, 1000));
        }
        int bf_result{bin_packing_best_fit(v)};
        int wf_result{bin_packing_worst_fit(v)};
        if (bf_result < wf_result)
            ++best_fit_wins;
        else if (bf_result == wf_result)
            ++even;
        else
            ++worst_fit_wins;
    }
    std::cout << "best_fit_wins: " << best_fit_wins
              << " worst_fit_wins: " << worst_fit_wins << " even: " << even
              << "\n";
    return 0;
}
