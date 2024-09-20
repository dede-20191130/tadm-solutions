#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
constexpr std::array<char, 26> lowercase_letters{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, char const *argv[]) {
    std::vector<char> cp_low{lowercase_letters.cbegin(),
                             lowercase_letters.cend()};
    std::random_shuffle(cp_low.begin(), cp_low.end());

    std::ifstream inf{"../data/some-text.txt"};
    if (!inf) {
        std::cerr << "cannot open file" << std::endl;
        return 1;
    }
    std::ofstream outf{"../data/char-rotated-text.txt"};
    if (!outf) {
        std::cerr << "cannot operate file" << std::endl;
        return 1;
    }

    std::string strInput{};
    while (std::getline(inf, strInput)) {
        for (auto it{strInput.begin()}; it != strInput.end(); it++) {
            if (std::isalpha(*it)) {
                if (std::islower(*it))
                    *it = cp_low[*it - 'a'];
                else
                    *it = cp_low[*it - 'A'] ^ 32;
            }
        }
        outf << strInput << std::endl;
    }

    return 0;
}
