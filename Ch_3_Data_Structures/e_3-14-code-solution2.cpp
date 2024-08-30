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
    int size{0};

   public:
    Binary_search_tree() = delete;
    Binary_search_tree(std::initializer_list<T> list) {
        for (auto &&e : list) insert_tree(e);
    };

    /*
    Insert all elements in the first tree.
    Then traverse incomplete linked list and the second tree,
    and insert elements of the tree one by one into the appropriate position

    Time complexity: O(n)
    n is a length of larger one of two trees.
    */
    static std::list<T> merge_to_list(const Binary_search_tree<T> &bs_tree1,
                                      const Binary_search_tree<T> &bs_tree2) {
        std::list<T> lst{};
        bs_tree1.traverse(
            [&lst](const p_tree tree) { lst.push_back(tree->item); });
        auto it_lst{lst.begin()};
        bs_tree2.traverse([&lst, &it_lst](const p_tree tree) {
            while (it_lst != lst.end() && *it_lst <= tree->item) ++it_lst;
            lst.insert(it_lst, tree->item);
        });
        return lst;
    }

    template <std::regular_invocable<p_tree> Func>
    void traverse(const Func func) const {
        auto helper{[&func](auto helper, const p_tree tree) -> void {
            if (tree) {
                helper(helper, tree->left);
                func(tree);
                helper(helper, tree->right);
            }
        }};
        helper(helper, root);
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
        auto helper{[&](auto helper, p_tree parent) -> void {
            p_tree *p_tree;
            if (val < parent->item)
                p_tree = &(parent->left);
            else
                p_tree = &(parent->right);
            if (!(*p_tree)) {
                *p_tree = std::make_shared<tree>(val, parent, nullptr, nullptr);
                return;
            } else {
                helper(helper, *p_tree);
            }
        }};
        if (!root) {
            root = std::make_shared<tree>(val, nullptr, nullptr, nullptr);
        } else
            helper(helper, root);
        ++size;
    }
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