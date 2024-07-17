#include <array>
#include <cassert>
#include <concepts>
#include <stdexcept>
constexpr unsigned int CAPACITY = 256;

template <class T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T>
class Stack {
   private:
    unsigned int i_top;
    T max;  // max value tracer
    T min;  // min value tracer
    std::array<T, CAPACITY> data;

   public:
    Stack() : i_top{0} {};
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    void push(T item) {
        if (CAPACITY <= i_top + 1) throw std::out_of_range("Capacity is over");
        if (!i_top) {
            data[i_top++] = item;
            max = item;
            min = item;
        } else if (item < min) {
            // insett item+(item-min): value and the diff from previous min
            data[i_top++] = item * 2 - min;
            min = item;
        } else if (max < item) {
            // insett item+(item-max): value and the diff from previous max
            data[i_top++] = item * 2 - max;
            max = item;
        } else {
            data[i_top++] = item;
        }
    }
    T pop() {
        if (!i_top) throw std::out_of_range("No item");
        auto v_top{data[--i_top]};
        if (v_top < min) {
            auto result{min};
            // restore previous min from the inserted value
            min = min * 2 - v_top;
            return result;
        } else if (max < v_top) {
            auto result{max};
            // restore previous max from the inserted value
            max = max * 2 - v_top;
            return result;
        } else
            return v_top;
    }
    T top() const {
        if (!i_top) throw std::out_of_range("No item");
        auto v_top{data[i_top - 1]};
        return v_top < min ? min : max < v_top ? max : v_top;
    }
    T find_min() const {
        if (!i_top) throw std::out_of_range("No item");
        return min;
    }
    T find_max() const {
        if (!i_top) throw std::out_of_range("No item");
        return max;
    }
};

int main(int argc, char const* argv[]) {
    Stack<int> st{};
    st.push(10);
    assert(st.find_min() == 10);
    assert(st.find_max() == 10);
    assert(st.top() == 10);
    st.push(11);
    assert(st.find_min() == 10);
    assert(st.find_max() == 11);
    assert(st.top() == 11);
    st.push(9);
    assert(st.find_min() == 9);
    assert(st.find_max() == 11);
    assert(st.top() == 9);
    st.push(-3);
    assert(st.find_min() == -3);
    assert(st.find_max() == 11);
    assert(st.top() == -3);
    st.push(-2);
    assert(st.find_min() == -3);
    assert(st.find_max() == 11);
    assert(st.top() == -2);
    st.push(5);
    assert(st.find_min() == -3);
    assert(st.find_max() == 11);
    assert(st.top() == 5);
    st.push(16);
    assert(st.find_min() == -3);
    assert(st.find_max() == 16);
    assert(st.top() == 16);
    st.push(15);
    assert(st.find_min() == -3);
    assert(st.find_max() == 16);
    assert(st.top() == 15);
    st.push(-8);
    assert(st.find_min() == -8);
    assert(st.find_max() == 16);
    assert(st.top() == -8);

    assert(st.pop() == -8);
    assert(st.find_min() == -3);
    assert(st.find_max() == 16);
    assert(st.top() == 15);

    assert(st.pop() == 15);
    assert(st.find_min() == -3);
    assert(st.find_max() == 16);
    assert(st.top() == 16);

    assert(st.pop() == 16);
    assert(st.find_min() == -3);
    assert(st.find_max() == 11);
    assert(st.top() == 5);

    assert(st.pop() == 5);
    assert(st.find_min() == -3);
    assert(st.find_max() == 11);
    assert(st.top() == -2);

    assert(st.pop() == -2);
    assert(st.find_min() == -3);
    assert(st.find_max() == 11);
    assert(st.top() == -3);

    assert(st.pop() == -3);
    assert(st.find_min() == 9);
    assert(st.find_max() == 11);
    assert(st.top() == 9);

    assert(st.pop() == 9);
    assert(st.find_min() == 10);
    assert(st.find_max() == 11);
    assert(st.top() == 11);

    assert(st.pop() == 11);
    assert(st.find_min() == 10);
    assert(st.find_max() == 10);
    assert(st.top() == 10);

    assert(st.pop() == 10);
    try {
        st.find_min();
    } catch (const std::out_of_range& e) {
        assert(std::string{e.what()}.compare("No item") == 0);
    }
    return 0;
}
