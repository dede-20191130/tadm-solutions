#ifndef impl_singly_linked_list
#define impl_singly_linked_list

#include <concepts>
#include <memory>

template <std::equality_comparable T>
struct node {
    T item;
    std::shared_ptr<node> next;
};

template <std::equality_comparable T>
class Singly_linked_list {
    using mnode = node<T>;

   private:
    std::shared_ptr<mnode> head;
    unsigned int m_size;

   public:
    Singly_linked_list() = default;
    Singly_linked_list(const Singly_linked_list&) = delete;
    Singly_linked_list(Singly_linked_list&&) = delete;
    Singly_linked_list(std::initializer_list<T> list)
        : m_size{static_cast<unsigned int>(list.size())} {
        if (!m_size) return;
        auto p_l{std::cbegin(list)};
        head = std::make_shared<mnode>(*p_l++);
        auto prev{head};
        for (; p_l != std::cend(list); p_l++) {
            auto p_node = std::make_shared<mnode>(*p_l);
            prev->next = p_node;
            prev = p_node;
        }
    }
    ~Singly_linked_list() {};
    Singly_linked_list& operator=(const Singly_linked_list&) = delete;

    unsigned int size() { return m_size; }

    std::shared_ptr<mnode> search(T val) {
        for (auto nd{head}; nd; nd = nd->next)
            if (nd->item == val) return nd;
        return nullptr;
    }

    void insert(T val) {
        head = std::make_shared<mnode>(val, head);
        ++m_size;
    }

    T head_val() { return head->item; }
    T tail_val() {
        std::shared_ptr<mnode> prev;
        for (auto nd{head}; nd; nd = nd->next) prev = nd;
        return prev->item;
    }

    template <std::regular_invocable<T> Func>
    void traverse(Func func) {
        std::shared_ptr<mnode> p_node;
        std::shared_ptr<mnode> next{head};
        while (next) {
            p_node = next;
            func(p_node->item);
            next = p_node->next;
        }
    }
};
#endif