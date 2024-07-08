#include <cassert>
#include <string>

constexpr char PAREN_OPEN{'('};
constexpr char PAREN_CLOSE{')'};

struct Balance_parenthesis {
    bool balanced;
    int offending_pos;
};

Balance_parenthesis check_bal(std::string_view target) {
    // loop to examine whole charactors
    // if ( exists, counter++
    // if ) exists, counter--
    // if counter < 0, record the position and return the result
    int cnt{0};
    std::size_t sz{target.size()};
    for (int i = 0; i < sz; i++) {
        if (target[i] == PAREN_OPEN) ++cnt;
        if (target[i] == PAREN_CLOSE) --cnt;
        if (cnt < 0) return {false, i};
    }
    return {true, -1};
}

int main(int argc, char const* argv[]) {
    std::string s{"()"};
    assert(check_bal(s).balanced);
    s = "(a)b(c)";
    assert(check_bal(s).balanced);
    s = "((())())()";
    assert(check_bal(s).balanced);
    s = ")()( ";
    auto result{check_bal(s)};
    assert(!result.balanced && result.offending_pos == 0);
    s = "())";
    result = check_bal(s);
    assert(!result.balanced && result.offending_pos == 2);
    s = "std::size_t sz{target.size()};";
    assert(check_bal(s).balanced);
    return 0;
}
