#ifndef BST_H
#define BST_H

#include <functional>
#include <cstddef>
#include <iostream>

using std::size_t;
using std::ostream;
using std::cout;
using std::endl;

class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        bool operator==(int val) const;
        bool operator>(int val) const;
        bool operator<(int val) const;
        bool operator>=(int val) const;
        bool operator<=(int val) const;

        int value;
        Node* left;
        Node* right;
    };

public:
    BST();
    BST(BST& bst);
    BST(BST&& bst) noexcept ;
    Node*& get_root();
    void bfs(const std::function<void(Node*& node)>& func);
    size_t length();
    bool add_node(int val);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    ostream& operator<<(ostream&);
    BST& operator++();
    const BST operator++(int);
    BST& operator=(BST& bst);
    BST& operator=(BST&& src);
    ~BST();


private:
    Node* root{};
};

bool operator==(int val, BST::Node& node);
bool operator> (int val, BST::Node& node);
bool operator< (int val, BST::Node& node);
bool operator>=(int val, BST::Node& node);
bool operator<=(int val, BST::Node& node);
ostream& operator<<(ostream& os, BST::Node& node);
ostream& operator<<(ostream& os, BST& bst);

#endif //BST_H