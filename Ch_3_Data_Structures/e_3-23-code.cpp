#include <cassert>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

constexpr std::string_view SPACE{" "};

template <std::totally_ordered T>
class Binary_search_tree {
   protected:
    struct tree {
        T item;
        std::shared_ptr<tree> parent;
        std::shared_ptr<tree> left;
        std::shared_ptr<tree> right;
    };
    using p_tree = std::shared_ptr<tree>;

    p_tree root;
    int size{0};

    bool check_balanced_impl(p_tree p_root) const {
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

    static Binary_search_tree<T> create_height_balanced(
        const Binary_search_tree<T> &bs_tree) {
        // convert into sorted array
        std::vector<T> v{bs_tree.begin(), bs_tree.end()};

        // Create tree-node by median index and
        // attach subtrees (recursion)
        Binary_search_tree<T> balanced_tree{};
        const auto helper{[&v](const auto helper, const size_t idx_min,
                               const size_t idx_max) -> p_tree {
            if (idx_max < idx_min)
                return nullptr;
            else if (idx_min == idx_max)
                return std::make_shared<tree>(v[idx_min], nullptr, nullptr,
                                              nullptr);

            size_t idx_mid{(idx_min + idx_max) / 2};
            auto tree_node{
                std::make_shared<tree>(v[idx_mid], nullptr, nullptr, nullptr)};

            p_tree left_chld{nullptr};
            if (0 < idx_mid) left_chld = helper(helper, idx_min, idx_mid - 1);
            auto right_chld{helper(helper, idx_mid + 1, idx_max)};

            tree_node->left = left_chld;
            tree_node->right = right_chld;
            if (left_chld) left_chld->parent = tree_node;
            if (right_chld) right_chld->parent = tree_node;

            return tree_node;
        }};
        balanced_tree.root = helper(helper, 0, v.size() - 1);
        balanced_tree.size = v.size();

        return balanced_tree;
    }

    int get_size() const { return size; };

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

    bool check_balanced_impl() const { return check_balanced_impl(root); }
};

class Printable_str_tree : public Binary_search_tree<std::string> {
   public:
    void print_all_prefixed(std::ostream &o, const std::string_view prefix) {
        const auto compare_prefix{[](const std::string_view text,
                                     const std::string_view prefix) -> int {
            return text.compare(0, prefix.size(), prefix);
        }};

        const auto helper{[&](auto helper, p_tree tree, p_tree lbound,
                              p_tree ubound) -> void {
            if (!tree || (lbound && 0 < compare_prefix(lbound->item, prefix)) ||
                (ubound && compare_prefix(ubound->item, prefix) < 0))
                return;
            if (!compare_prefix(tree->item, prefix)) o << tree->item << SPACE;

            helper(helper, tree->left, lbound, tree);
            helper(helper, tree->right, tree, ubound);
        }};
        helper(helper, root, nullptr, nullptr);
    }
};

auto split(const std::string &s, const std::string_view delim) {
    std::vector<std::string> result;
    size_t pos{0};
    size_t p_data_stt{0};
    while ((pos = s.find(delim, pos)) != std::string::npos) {
        if (p_data_stt != pos) {
            result.push_back(s.substr(p_data_stt, pos - p_data_stt));
            p_data_stt = pos + 1;
        }
        ++pos;
    }

    return result;
}

int main(int argc, char const *argv[]) {
    Printable_str_tree str_tree{{"a", "b"}};
    std::ostringstream ss;

    str_tree.print_all_prefixed(ss, "a");
    auto printeds{split(ss.str(), SPACE)};
    std::sort(printeds.begin(), printeds.end());
    assert(printeds == (std::vector<std::string>{"a"}));
    ss.str("");
    ss.clear();

    str_tree.print_all_prefixed(ss, "b");
    printeds = split(ss.str(), SPACE);
    std::sort(printeds.begin(), printeds.end());
    assert(printeds == (std::vector<std::string>{"b"}));
    ss.str("");
    ss.clear();

    str_tree.print_all_prefixed(ss, "c");
    printeds = split(ss.str(), SPACE);
    std::sort(printeds.begin(), printeds.end());
    assert(!printeds.size());
    ss.str("");
    ss.clear();

    str_tree = {{"abc", "ade", "abd", "adf"}};

    str_tree.print_all_prefixed(ss, "a");
    printeds = split(ss.str(), SPACE);
    std::sort(printeds.begin(), printeds.end());
    assert(printeds == (std::vector<std::string>{"abc", "abd", "ade", "adf"}));
    ss.str("");
    ss.clear();

    str_tree.print_all_prefixed(ss, "ab");
    printeds = split(ss.str(), SPACE);
    std::sort(printeds.begin(), printeds.end());
    assert(printeds == (std::vector<std::string>{"abc", "abd"}));
    ss.str("");
    ss.clear();

    str_tree.print_all_prefixed(ss, "ad");
    printeds = split(ss.str(), SPACE);
    std::sort(printeds.begin(), printeds.end());
    assert(printeds == (std::vector<std::string>{"ade", "adf"}));
    ss.str("");
    ss.clear();

    str_tree = {{"pd", "qd", "pi", "qb", "ow", "od", "pj",
                 "oe", "pa", "pf", "ph", "ob", "pe", "pc",
                 "qc", "oa", "oc", "pb", "ox", "qa", "pg"}};

    str_tree.print_all_prefixed(ss, "p");
    printeds = split(ss.str(), SPACE);
    std::sort(printeds.begin(), printeds.end());
    assert(printeds ==
           (std::vector<std::string>{"pa", "pb", "pc", "pd", "pe", "pf", "pg",
                                     "ph", "pi", "pj"}));
    ss.str("");
    ss.clear();

    return 0;
}
