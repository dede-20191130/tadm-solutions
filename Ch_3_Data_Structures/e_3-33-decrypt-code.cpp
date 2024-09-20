// frequency of letters:
//  http://en.algoritmy.net/article/40379/Letter-frequency-English
#include <algorithm>
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

constexpr std::array<char, 26> freq_order{
    'z', 'q', 'x', 'j', 'k', 'v', 'b', 'p', 'y', 'g', 'f', 'w', 'm',
    'u', 'c', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e',
};

struct Char_counter {
    char counterpart_freq_char;
    size_t orig_pos;
    unsigned long cnt{0};
};

int main(int argc, char const *argv[]) {
    std::vector<Char_counter> v_char(26);
    for (size_t i = 0; i < v_char.size(); i++) {
        v_char[i].orig_pos = i;
    }

    std::ifstream inf{"../data/char-rotated-text.txt"};
    if (!inf) {
        std::cerr << "cannot open file" << std::endl;
        return 1;
    }
    // read frequency information of the input file
    std::string strInput{};
    while (std::getline(inf, strInput)) {
        for (auto it{strInput.cbegin()}; it != strInput.cend(); it++) {
            if (std::isalpha(*it)) {
                auto c{*it};
                if (std::islower(c))
                    v_char[c - 'a'].cnt++;
                else
                    v_char[c - 'A'].cnt++;
            }
        }
    }
    // sort the result and link the letter in frequency table with the result
    std::sort(v_char.begin(), v_char.end(),
              [](auto e1, auto e2) { return e1.cnt < e2.cnt; });
    for (size_t i = 0; i < v_char.size(); i++) {
        v_char[i].counterpart_freq_char = freq_order[i];
    }
    // resort to restore the order
    std::sort(v_char.begin(), v_char.end(),
              [](auto e1, auto e2) { return e1.orig_pos < e2.orig_pos; });
    // read again and convert letters with the appropriate frequency letters
    // save the result to output file
    std::ofstream outf{"../data/char-rerolated-text.txt"};
    if (!outf) {
        std::cerr << "cannot operate file" << std::endl;
        return 1;
    }
    inf.clear();
    inf.seekg(0);
    while (std::getline(inf, strInput)) {
        for (auto it{strInput.begin()}; it != strInput.end(); it++) {
            if (std::isalpha(*it)) {
                if (std::islower(*it))
                    *it = v_char[*it - 'a'].counterpart_freq_char;
                else
                    *it = v_char[*it - 'A'].counterpart_freq_char - 32;
            }
        }
        outf << strInput << std::endl;
    }
    return 0;
}
