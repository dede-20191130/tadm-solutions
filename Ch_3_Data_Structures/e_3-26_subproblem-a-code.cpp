#include <cassert>
#include <stdexcept>
#include <vector>

// --strategy--
// parse the array to the 'cheat sheet' data structure:
//  - each element has:
//      - corresponding integer data
//      - array containing an indices of the mininum number
//          the index corresponds the difference between
//              the start and end index of the interval
class Seeker_smallest_order_constant {
   private:
    struct Parsed_elem {
        int num;
        std::vector<size_t> minimum_idxs;
    };
    std::vector<Parsed_elem> elems;

   public:
    Seeker_smallest_order_constant(std::initializer_list<int> lst) {
        std::vector<int> v{lst};
        for (size_t i = 0; i < v.size(); i++) {
            auto &pe{elems.emplace_back(v[i])};
            auto minimum_idx{i};
            for (size_t j = i; j < v.size(); j++) {
                if (v[j] < v[minimum_idx]) minimum_idx = j;
                pe.minimum_idxs.push_back(minimum_idx);
            }
        }
    }
    int seek_the_min(size_t start, size_t end) {
        if (elems.size() <= end || end < start)
            throw std::invalid_argument("Not valid");
        return elems[elems[start].minimum_idxs[end - start]].num;
    }
};

int main(int argc, char const *argv[]) {
    Seeker_smallest_order_constant seeker{1};
    assert(seeker.seek_the_min(0, 0) == 1);

    seeker = {1, 2};
    assert(seeker.seek_the_min(0, 0) == 1);
    assert(seeker.seek_the_min(0, 1) == 1);
    assert(seeker.seek_the_min(1, 1) == 2);
    seeker = {2, 1};
    assert(seeker.seek_the_min(0, 0) == 2);
    assert(seeker.seek_the_min(0, 1) == 1);
    assert(seeker.seek_the_min(1, 1) == 1);

    seeker = {30, 40, 10, 50, 80, 60, 20};
    assert(seeker.seek_the_min(0, 0) == 30);
    assert(seeker.seek_the_min(0, 1) == 30);
    assert(seeker.seek_the_min(0, 2) == 10);
    assert(seeker.seek_the_min(0, 6) == 10);
    assert(seeker.seek_the_min(1, 3) == 10);
    assert(seeker.seek_the_min(2, 4) == 10);
    assert(seeker.seek_the_min(3, 5) == 50);
    assert(seeker.seek_the_min(4, 6) == 20);
    assert(seeker.seek_the_min(3, 6) == 20);
    return 0;
}
