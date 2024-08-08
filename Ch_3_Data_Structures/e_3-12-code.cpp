#include <cassert>
#include <concepts>
#include <initializer_list>
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
    Binary_search_tree(std::initializer_list<T> list) {
        for (auto &&e : list) insert_tree(e);
    };
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
    int get_max_depth() {
        int max_d{0};
        int rest_of_elem{size};
        auto helper{[&](auto helper, p_tree tree, int curr_d) -> bool {
            // if tree is null, exit
            if (!tree) return true;
            // update the max_depth
            max_d = std::max(max_d, curr_d);
            // decrement the rest of elements
            --rest_of_elem;

            // recurse for the left and right subtrees
            if (!helper(helper, tree->left, curr_d + 1)) return false;

            // if the diff between max_degth_at_that_time and current_depth
            //  is greater than rest_of_elements, stop the
            //  sebsequent recursion
            if ((max_d - curr_d) > rest_of_elem) return false;

            if (!helper(helper, tree->right, curr_d + 1)) return false;
            return true;
        }};
        helper(helper, root, 0);
        return max_d;
    }
};

int main(int argc, char const *argv[]) {
    {
        Binary_search_tree<int> tree{1, 2, 3, 4, 5};
        assert(tree.get_max_depth() == 4);
    }
    {
        Binary_search_tree<int> tree{5, 4, 3, 2, 1};
        assert(tree.get_max_depth() == 4);
    }
    {
        Binary_search_tree<int> tree{3, 2, 4, 1, 5};
        assert(tree.get_max_depth() == 2);
    }
    {
        Binary_search_tree<int> tree{1, 4, 3, 2, 5};
        assert(tree.get_max_depth() == 3);
        tree.insert_tree(-5);
        assert(tree.get_max_depth() == 3);
        tree.insert_tree(10);
        assert(tree.get_max_depth() == 3);
        tree.insert_tree(20);
        assert(tree.get_max_depth() == 4);
        tree.insert_tree(6);
        assert(tree.get_max_depth() == 4);
        tree.insert_tree(9);
        assert(tree.get_max_depth() == 5);
        tree.insert_tree(7);
        assert(tree.get_max_depth() == 6);
    }
    return 0;
}
