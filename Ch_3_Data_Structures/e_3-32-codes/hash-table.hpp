#ifndef impl_hash_table
#define impl_hash_table

#include <algorithm>
#include <concepts>
#include <vector>

#include "./singly-linked-list.hpp"

constexpr size_t T_SIZE{1 << 12};

template <class T>
class Hash_table {
   private:
    std::vector<Singly_linked_list<T>> table;
    std::vector<Singly_linked_list<T> *> refs;

   public:
    Hash_table() : table(T_SIZE) {}
    Hash_table(std::initializer_list<T> lst) : Hash_table() {
        for (auto &&e : lst) {
            insert(e);
        }
    }
    void insert(T e) {
        std::hash<T> hasher{};
        auto hash(hasher(e));
        auto &lst{table[hash % T_SIZE]};
        auto it{lst.search(e)};
        if (!it) {
            if (!lst.size()) refs.push_back(&lst);
            lst.insert(e);
        }
    }
    void insert(std::vector<T> &v) {
        for (auto &&e : v) insert(e);
    }

    template <std::regular_invocable<T> Func>
    void traverse(Func func) {
        for (const auto lst : refs) {
            lst->traverse(func);
        }
    }
};

#endif