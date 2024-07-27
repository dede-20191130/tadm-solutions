#include <cassert>
#include <concepts>
#include <memory>
#include <string>

template <std::equality_comparable T>
class Singly_linked_list {
   private:
    struct node {
        T item;
        std::shared_ptr<node> next;
    };
    std::shared_ptr<node> head;
    unsigned int m_size;

   public:
    Singly_linked_list() = delete;
    Singly_linked_list(const Singly_linked_list&) = delete;
    Singly_linked_list(Singly_linked_list&&) = delete;
    Singly_linked_list(std::initializer_list<T> list)
        : m_size{static_cast<unsigned int>(list.size())} {
        if (!m_size) return;
        auto p_l{std::cbegin(list)};
        head = std::make_shared<node>(*p_l++);
        auto prev{head};
        for (; p_l != std::cend(list); p_l++) {
            auto p_node = std::make_shared<node>(*p_l);
            prev->next = p_node;
            prev = p_node;
        }
    }
    ~Singly_linked_list(){};
    Singly_linked_list& operator=(const Singly_linked_list&) = delete;

    unsigned int size() { return m_size; }

    std::shared_ptr<node> search(T val) {
        for (auto nd{head}; nd; nd = nd->next)
            if (nd->item == val) return nd;
        return nullptr;
    }

    void insert(T val) {
        head = std::make_shared<node>(val, head);
        ++m_size;
    }

    // implement delete running in constant time
    void delete_n(std::shared_ptr<node> target) {
        // if target is head, simply deallocate and the next head is 'next'
        // (O(1) time complexity)
        if (target == head) {
            head = head->next;
            --m_size;
            return;
        }

        // if target is tail, search the new tail and deallocate previous tail
        // (O(n) time complexity)
        if (!target->next) {
            for (auto nd{head}; nd;) {
                auto prev{nd};
                nd = nd->next;
                if (nd == target) {
                    prev->next = nullptr;
                    --m_size;
                    return;
                }
            }
            return;
        }

        // overwrite the value with the next value
        // deallocate the next node
        // reconnect target node and the node after next
        // (O(1) time complexity)
        target->item = target->next->item;
        target->next = target->next->next;
        --m_size;
    }

    T head_val() { return head->item; }
    T tail_val() {
        std::shared_ptr<node> prev;
        for (auto nd{head}; nd; nd = nd->next) prev = nd;
        return prev->item;
    }
};

int main(int argc, char const* argv[]) {
    Singly_linked_list<int> ll{1, 2, 3, 4, 5, 6, 7};
    assert(ll.size() == 7);
    assert(ll.head_val() == 1);
    assert(ll.tail_val() == 7);
    ll.insert(-10);
    assert(ll.size() == 8);
    assert(ll.head_val() == -10);
    assert(ll.tail_val() == 7);
    auto l_node{ll.search(-10)};
    assert(l_node->item == -10);
    ll.delete_n(l_node);
    assert(ll.size() == 7);
    assert(ll.head_val() == 1);
    assert(ll.tail_val() == 7);
    l_node = ll.search(7);
    ll.delete_n(l_node);
    assert(ll.size() == 6);
    assert(ll.head_val() == 1);
    assert(ll.tail_val() == 6);
    l_node = ll.search(5);
    ll.delete_n(l_node);
    assert(ll.size() == 5);
    assert(ll.head_val() == 1);
    assert(ll.tail_val() == 6);
    l_node = ll.search(3);
    ll.delete_n(l_node);
    assert(ll.size() == 4);
    assert(ll.head_val() == 1);
    assert(ll.tail_val() == 6);
    l_node = ll.search(9999);
    assert(l_node == nullptr);

    return 0;
}
