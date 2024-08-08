#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

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

    void swap_val(p_tree t1, p_tree t2) {
        T tmp{t1->item};
        t1->item = t2->item;
        t2->item = tmp;
    }

    // Traverse the tree in order
    // The value of node must be increaced in order, too.
    // If they violates, return false, otherwise return true
    bool check_balanced_impl(p_tree p_root) {
        T curr{};
        bool undefined_val{true};
        auto helper{[&](auto helper, p_tree tree) -> bool {
            if (!tree) return true;
            if (!helper(helper, tree->left)) return false;
            if (undefined_val) {
                undefined_val = false;
            } else if (tree->item < curr)
                return false;
            curr = tree->item;
            return helper(helper, tree->right);
        }};
        return helper(helper, p_root);
    }

   public:
    Binary_search_tree(std::initializer_list<T> list) {
        for (auto &&e : list) insert_tree(e);
    };
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
    bool check_balanced() { return check_balanced_impl(root); }

    // For test of mistaken situation
    void swap_target_2(p_tree tr1, p_tree tr2) { swap_val(tr1, tr2); }

    /*
    Traverse the tree in order
    The value of node must be increaced in order, too.

    When there is a violation, record the previous node and current node.
    Continue the check of sanity of value from the next node.
    If there is additional violation, record the node and return the two.
    Else, return the recored prevous node and the node in which violation
    occured.
     */
    std::pair<p_tree, p_tree> identify_swapped() {
        std::vector<p_tree> to_be_swappeds;
        p_tree prev{nullptr};
        auto helper{[&](auto helper, p_tree tree) -> bool {
            if (!tree) return true;
            if (!helper(helper, tree->left)) return false;
            if (prev && tree->item < prev->item) {
                if (!to_be_swappeds.size()) {
                    to_be_swappeds.push_back(prev);
                    to_be_swappeds.push_back(tree);
                } else {
                    to_be_swappeds.back() = tree;
                    return false;
                }
            }
            prev = tree;
            return helper(helper, tree->right);
        }};
        helper(helper, root);
        return {to_be_swappeds.front(), to_be_swappeds.back()};
    }

    void correct_swapped() {
        auto to_be_swapped{identify_swapped()};
        swap_val(to_be_swapped.first, to_be_swapped.second);
    }
};

int main(int argc, char const *argv[]) {
    Binary_search_tree<int> tree{8, 4, 12, 2, 6,  10, 14, 1,
                                 3, 5, 7,  9, 11, 13, 15, 16};
    auto test_swapping_2{[&tree](int i1, int i2) {
        assert(tree.check_balanced());
        auto tr_node1{tree.search_tree(i1)};
        auto tr_node2{tree.search_tree(i2)};
        tree.swap_target_2(tr_node1, tr_node2);
        assert(!tree.check_balanced());
        tree.correct_swapped();
        assert(tree.check_balanced());
    }};
    test_swapping_2(8, 4);
    test_swapping_2(8, 2);
    test_swapping_2(8, 1);
    test_swapping_2(4, 1);
    test_swapping_2(2, 1);
    test_swapping_2(4, 6);
    test_swapping_2(4, 5);
    test_swapping_2(2, 6);
    test_swapping_2(1, 6);
    test_swapping_2(1, 7);
    test_swapping_2(4, 12);
    test_swapping_2(4, 9);
    test_swapping_2(4, 16);
    test_swapping_2(2, 14);
    test_swapping_2(2, 15);
    test_swapping_2(2, 16);
    test_swapping_2(5, 13);
    return 0;
}
