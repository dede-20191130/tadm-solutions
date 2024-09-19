#include <chrono>
#include <concepts>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "./binary-search-tree.hpp"
#include "./hash-table.hpp"
#include "./red-black-tree.hpp"
#include "./singly-linked-list.hpp"

using namespace std::string_literals;

class Base_dic {
   protected:
    std::string output_name;
    void print_s(std::ostream& o, std::string_view s) { o << s << std::endl; }

   public:
    Base_dic(std::string_view sv) : output_name{sv} {}
    virtual ~Base_dic() = default;
    virtual void insert(std::string& s) = 0;
    virtual void print_all(std::ofstream& outf) = 0;
    std::string_view get_output_name() const { return output_name; }
};

class SLL_dic : public Base_dic {
   private:
    Singly_linked_list<std::string> lst{};

   public:
    virtual ~SLL_dic() = default;
    SLL_dic() : Base_dic("singly-linked-list-result") {}
    void insert(std::string& s) override {
        auto pnode{lst.search(s)};
        if (!pnode) lst.insert(s);
    }
    void print_all(std::ofstream& outf) {
        lst.traverse([&](std::string e) { print_s(outf, e); });
    };
};

class BST_dic : public Base_dic {
   private:
    Binary_search_tree<std::string> bst{};

   public:
    virtual ~BST_dic() = default;
    BST_dic() : Base_dic("binary-serach-tree-result") {}
    void insert(std::string& s) override { bst.insert_tree(s); }
    void print_all(std::ofstream& outf) {
        bst.traverse([&](Binary_search_tree<std::string>::p_tree p_tree) {
            print_s(outf, p_tree->item);
        });
    };
};

class RBT_dic : public Base_dic {
   private:
    RedBlackTree<std::string> bst{};

   public:
    virtual ~RBT_dic() = default;
    RBT_dic() : Base_dic("red-black-tree-result") {}
    void insert(std::string& s) override { bst.insert(s); }
    void print_all(std::ofstream& outf) {
        bst.traverse([&](pNode<std::string> p_node) {
            if (p_node->data.length()) print_s(outf, p_node->data);
        });
    };
};

class HT_dic : public Base_dic {
   private:
    Hash_table<std::string> bst{};

   public:
    virtual ~HT_dic() = default;
    HT_dic() : Base_dic("hash-table-result") {}
    void insert(std::string& s) override { bst.insert(s); }
    void print_all(std::ofstream& outf) {
        bst.traverse([&](std::string s) { print_s(outf, s); });
    };
};

template <typename Dic>
    requires std::derived_from<Dic, Base_dic>
void count_words(std::ifstream& inf, Dic& dic) {
    std::string s;
    while (inf >> s) {
        dic.insert(s);
    }

    std::ostringstream name;
    name << "./"s << dic.get_output_name() << ".txt"s;
    std::ofstream outf{name.str()};
    dic.print_all(outf);
}

template <std::regular_invocable<> Func>
void measure_time(std::ofstream& outf, Func func,
                  std::string_view target_name) {
    auto start = chrono::high_resolution_clock::now();
    auto erapsed{
        [&]() { return chrono::high_resolution_clock::now() - start; }};

    auto get_milli_ticks{[](const std::chrono::nanoseconds& d) {
        return chrono::duration_cast<chrono::milliseconds>(d).count();
    }};

    func();

    outf << "Erapsed time for " << target_name << ":"
         << get_milli_ticks(erapsed()) << " milliseconds." << std::endl;
}

int main(int argc, char const* argv[]) {
    std::vector<std::shared_ptr<Base_dic>> vdic;
    vdic.push_back(std::shared_ptr<Base_dic>(new SLL_dic{}));
    vdic.push_back(std::shared_ptr<Base_dic>(new BST_dic{}));
    vdic.push_back(std::shared_ptr<Base_dic>(new RBT_dic{}));
    vdic.push_back(std::shared_ptr<Base_dic>(new HT_dic{}));

    std::ifstream inf{"./some-text.txt"};
    if (!inf) {
        std::cerr << "cannot open file" << std::endl;
        return 1;
    }
    std::ofstream outf{"./result-time.txt"};
    if (!outf) {
        std::cerr << "cannot operate file" << std::endl;
        return 1;
    }

    outf.imbue(std::locale("en_US.UTF-8"));

    for (auto&& dic : vdic) {
        auto count_words_for{[&]() { count_words(inf, *dic); }};
        measure_time(outf, count_words_for, dic->get_output_name());
        inf.clear();
        inf.seekg(0);
    }

    return 0;
}
