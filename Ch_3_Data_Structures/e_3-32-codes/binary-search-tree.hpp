#ifndef impl_binary_search_tree
#define impl_binary_search_tree

#include <concepts>
#include <initializer_list>
#include <memory>

template <std::totally_ordered T>
class Binary_search_tree {
   public:
    struct tree {
        T item;
        std::shared_ptr<tree> parent;
        std::shared_ptr<tree> left;
        std::shared_ptr<tree> right;
    };
    using p_tree = std::shared_ptr<tree>;

   private:
    p_tree root;
    int size{0};

   public:
    Binary_search_tree(std::initializer_list<T> list) {
        for (auto &&e : list) insert_tree(e);
    };

    int get_size() const { return size; };

    template <std::regular_invocable<p_tree> Func>
    void traverse(Func func) {
        const auto helper{[&](auto helper, const p_tree tree) -> void {
            if (tree) {
                helper(helper, tree->left);
                func(tree);
                helper(helper, tree->right);
            }
        }};
        helper(helper, root);
    }

    void insert_tree(T val) {
        auto helper{[&](auto helper, p_tree parent, bool is_min) -> void {
            p_tree *p_tree;
            if (val < parent->item)
                p_tree = &(parent->left);
            else if (val == parent->item)
                return;
            else {
                p_tree = &(parent->right);
                is_min = false;
            }
            if (!(*p_tree)) {
                *p_tree = std::make_shared<tree>(val, parent, nullptr, nullptr);
                return;
            } else {
                helper(helper, *p_tree, is_min);
            }
        }};
        if (!root) {
            root = std::make_shared<tree>(val, nullptr, nullptr, nullptr);
        } else
            helper(helper, root, true);
        ++size;
    }
};

#endif