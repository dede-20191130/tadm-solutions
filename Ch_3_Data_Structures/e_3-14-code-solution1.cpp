#include <cassert>
#include <concepts>
#include <initializer_list>
#include <list>
#include <memory>

template <std::totally_ordered T>
class Binary_search_tree {
   private:
    struct tree {
        T item;
        std::shared_ptr<tree> parent;
        std::shared_ptr<tree> left;
        std::shared_ptr<tree> right;
    };
    using p_tree = std::shared_ptr<tree>;
    p_tree root;
    p_tree tree_min{nullptr};
    int size{0};

   public:
    Binary_search_tree() = delete;
    Binary_search_tree(std::initializer_list<T> list) {
        for (auto &&e : list) insert_tree(e);
    };

    /*
    Using iterators, we examine both head of iterators of two tree and
    pick the smaller one and insert the linked list, then increment
    the picked iterator.
    This combination is similar to merge-routine in mergesort.

    Time complexity: O(n)
    n is a length of larger one of two trees.
    */
    static std::list<T> merge_to_list(const Binary_search_tree<T> &bs_tree1,
                                      const Binary_search_tree<T> &bs_tree2) {
        std::list<T> lst{};
        Iterator it1{bs_tree1.begin()};
        Iterator it2{bs_tree2.begin()};
        while (it1 != bs_tree1.end() && it2 != bs_tree2.end()) {
            if (*it1 < *it2)
                lst.push_back(*it1++);
            else
                lst.push_back(*it2++);
        }
        while (it1 != bs_tree1.end()) lst.push_back(*it1++);
        while (it2 != bs_tree1.end()) lst.push_back(*it2++);
        return lst;
    }

    p_tree search_tree(T searchee) {
        auto helper{[&](auto helper, p_tree tree) -> p_tree {
            if (!tree) return nullptr;
            if (tree->item == searchee)
                return tree;
            else if (searchee < tree->item)
                return helper(helper, tree->left);
            else
                return helper(helper, tree->right);
        }};
        return helper(helper, root);
    }

    void insert_tree(T val) {
        auto helper{[&](auto helper, p_tree parent, bool is_min) -> void {
            p_tree *p_tree;
            if (val < parent->item)
                p_tree = &(parent->left);
            else {
                p_tree = &(parent->right);
                is_min = false;
            }
            if (!(*p_tree)) {
                *p_tree = std::make_shared<tree>(val, parent, nullptr, nullptr);
                if (is_min) tree_min = *p_tree;
                return;
            } else {
                helper(helper, *p_tree, is_min);
            }
        }};
        if (!root) {
            tree_min = root =
                std::make_shared<tree>(val, nullptr, nullptr, nullptr);
        } else
            helper(helper, root, true);
        ++size;
    }

    // Iterator implementation for data to be exposed in order
    struct Iterator {
        Iterator() : current_node{nullptr} {};
        Iterator(p_tree node) : current_node{node} {};
        Iterator &operator++() {
            if (current_node->right) {
                current_node = current_node->right;
                while (current_node->left) current_node = current_node->left;
            } else {
                auto prev{current_node};
                current_node = current_node->parent;
                while (current_node) {
                    if (prev == current_node->left) break;
                    prev = current_node;
                    current_node = current_node->parent;
                }
            }
            return *this;
        }
        Iterator operator++(int) {
            Iterator it_temp{*this};
            ++(*this);
            return it_temp;
        }
        bool operator==(const Iterator &it) const {
            return this->current_node == it.current_node;
        }
        bool operator!=(const Iterator &it) const { return !(*this == it); }
        T operator*() const { return this->current_node->item; }

       private:
        p_tree current_node;
    };
    Iterator begin() const { return Iterator(tree_min); }
    Iterator end() const { return Iterator(); }
};

int main(int argc, char const *argv[]) {
    Binary_search_tree<int> tree1{10};
    Binary_search_tree<int> tree2{20};
    auto lst{Binary_search_tree<int>::merge_to_list(tree1, tree2)};
    assert(lst == (std::list<int>{10, 20}));

    tree1 = {20};
    tree2 = {10};
    lst = Binary_search_tree<int>::merge_to_list(tree1, tree2);
    assert(lst == (std::list<int>{10, 20}));

    tree1 = {4, 2, 6, 1, 3, 5, 7, 8};
    lst = Binary_search_tree<int>::merge_to_list(tree1, tree1);
    assert(lst ==
           (std::list<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8}));

    tree1 = {4, 2, 6, 1, 3, 5, 7, 8};
    tree2 = {8, 6, 10, 5, 7, 9, 11, 12};
    lst = Binary_search_tree<int>::merge_to_list(tree1, tree2);
    assert(lst ==
           (std::list<int>{1, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 10, 11, 12}));

    tree1 = {19, 1, 23, 15, 17, 9, 7, 5, 21, 13, 3, 11};
    tree2 = {4, 10, 18, 0, 12, 22, 14, 8, 2, 16, 20, 6};
    lst = Binary_search_tree<int>::merge_to_list(tree1, tree2);
    assert(lst ==
           (std::list<int>{0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                           12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23}));

    return 0;
}
