#include "bst.h"
#include <queue>
#include <iomanip>

BST::Node::Node(int value, Node* left, Node* right)
        : value(value), left(left), right(right) {}

BST::Node::Node() : Node(0, nullptr, nullptr) {}

BST::Node::Node(const Node& node)
        : value(node.value), left(node.left), right(node.right) {}

bool BST::Node::operator==(int val) const {
    return this->value == val;
}

bool BST::Node::operator>(int val) const {
    return this->value > val;
}

bool BST::Node::operator<(int val) const {
    return this->value < val;
}

bool BST::Node::operator>=(int val) const {
    return this->value >= val;
}

bool BST::Node::operator<=(int val) const {
    return this->value <= val;
}

bool operator==(int val, BST::Node& node) {
    return node.value == val;
}

bool operator> (int val, BST::Node& node) {
    return node < val;
}

bool operator< (int val, BST::Node& node) {
    return node > val;
}

bool operator>=(int val, BST::Node& node) {
    return node <= val;
}

bool operator<=(int val, BST::Node& node) {
    return node >= val;
}


ostream& operator<<(ostream& os, BST::Node& node) {
    os << std::left << std::setw(17) << &node;
    os << "=> value:";
    os << std::left << std::setw(10) << node.value << "left:";
    os << std::left << std::setw(16) << ((node.left == nullptr) ? nullptr : node.left);
    os << "right:";
    os << std::left << std::setw(16) << ((node.left == nullptr) ? nullptr : node.left);
    return os;
}

ostream& operator<<(ostream& os, BST& bst) {
    os << "********************************************************************************" << endl;
    bst.bfs([&](BST::Node*& node) -> void {os << *node << endl;});
    os << "********************************************************************************" << endl;
    return os;
}




BST::BST() : root(nullptr) {}

BST::BST(BST& bst) {
    if (bst.root == nullptr) {
        root = nullptr;
        return;
    }
    *root = Node(*(bst.root));
    if (bst.root->left == nullptr && bst.root->right == nullptr) {
        return;
    }
    int val = root -> value;
    std::queue<int> queue;
    queue.push(val);
    while (!queue.empty()) {
        val = queue.front();
        queue.pop();
        Node* src = *(bst.find_node(val));
        Node* dec = *(this->find_node(val));
        if (src->left != nullptr) {
            queue.push(src->left->value);
        }
        if (src->right != nullptr) {
            queue.push(src->right->value);
        }
        *(dec->left) = Node(*(src->left));
        *(dec->right) = Node(*(src->right));
    }
}

BST::BST(BST&& bst) noexcept : root(bst.root) {}

BST::Node*& BST::get_root() {
    return root;
}

void BST::bfs(const std::function<void(Node*& node)>& func) {
    if (root == nullptr) {
        return;
    }
    std::queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* node = queue.front();
        queue.pop();
        if (node->left) {
            queue.push(node->left);
        }
        if (node->right) {
            queue.push(node->right);
        }
        func(node);
    }
}

size_t BST::length() {
    if (root == nullptr) {
        return 0;
    }
    size_t length = 0;
    std::queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node* node = queue.front();
        queue.pop();
        if (node->left) {
            queue.push(node->left);
        }
        if (node->right) {
            queue.push(node->right);
        }
        length += 1;
    }

    return length;
}

bool BST::add_node(int value) {
    if (root == nullptr) {
        root = new BST::Node(value, nullptr, nullptr);
        return true;
    }
    Node* p = root;
    while (true) {
        if (*p < value) {
            if (p->right != nullptr) {
                p = p->right;
            } else {
                p->right = new BST::Node(value, nullptr, nullptr);
                break;
            }
        } else if (*p > value) {
            if (p->left != nullptr) {
                p = p->left;
            } else {
                p->left = new BST::Node(value, nullptr, nullptr);
                break;
            }
        } else {
            return false;
        }
    }

    return true;
}

BST::Node** BST::find_node(int value) {
    if (root == nullptr) {
        return nullptr;
    }
    Node** p = &root;
    while (true) {
        Node* ptr = *p;
        if (ptr->value < value) {
            if (ptr->right != nullptr) {
                p = &(ptr->right);
            } else {
                return nullptr;
            }
        } else if (ptr->value > value) {
            if (ptr->left != nullptr) {
                p = &(ptr->left);
            } else {
                return nullptr;
            }
        } else {
            return &(*p);
        }
    }
}

BST::Node** BST::find_parrent(int value) {
    if (root == nullptr) {
        return nullptr;
    }
    Node** p = &root;
    Node** parent = p;
    while (true) {
        Node* ptr = *p;
        if (ptr == nullptr) {
            return nullptr;
        }
        if (ptr->value > value) {
            parent = p;
            p = &(ptr -> left);
        } else if (ptr->value < value) {
            parent = p;
            p = &(ptr -> right);
        } else {
            return parent == p ? nullptr : &(*parent);
        }
    }
}

BST::Node** BST::find_successor(int value) {
    if (root == nullptr) {
        return nullptr;
    }
    Node** ansNode;
    Node** pNode = find_node(value);
    if (pNode == nullptr) {
        return nullptr;
    } else {
        if ((*pNode)->left) {
            ansNode = &((*pNode)->left);
            while ((*ansNode)->right) {
                ansNode = &((*ansNode)->right);
            }
            return ansNode;
        } else if ((*pNode)->right) {
            ansNode = &((*pNode)->right);
            while ((*ansNode)->left) {
                ansNode = &((*ansNode)->left);
            }
            return ansNode;
        } else {
            return nullptr;
        }
    }
}

bool BST::delete_node(int value) {
    Node** pNodeParent = find_parrent(value);
    if (pNodeParent == nullptr) {
        return false;
    }
    Node** pNode = find_node(value);
    if (pNode == nullptr) {
        return false;
    }
    Node** successor = find_successor(value);
    if (successor == nullptr) {
        if ((*pNodeParent)->left == *pNode) {
            (*pNodeParent)->left = nullptr;
            delete *pNode;
            return true;
        }
        if ((*pNodeParent)->right == *pNode) {
            (*pNodeParent)->right = nullptr;
            delete *pNode;
            return true;
        }
    }
    Node** successorParent = find_parrent((*successor)->value);
    Node* successorNodePtr = *successor;
    if ((*successorParent)->left == *successor) {
        (*successorParent)->left = nullptr;
    } else {
        (*successorParent)->right = nullptr;
    }
    successorNodePtr->left = (*pNode)->left;
    successorNodePtr->right = (*pNode)->right;
    Node* pNodePtr = *pNode;
    if ((*pNodeParent)->left == *pNode) {
        (*pNodeParent)->left = successorNodePtr;
    } else {
        (*pNodeParent)->right = successorNodePtr;
    }
    delete pNodePtr;
    return true;
}

BST& BST::operator++() {
    bfs([](BST::Node*& node) -> void {node->value += 1;});
    return *this;
}

const BST BST::operator++(int) {
    BST bst(*this);
    bfs([](BST::Node*& node) -> void {node->value += 1;});
    return bst;
}

BST& BST::operator=(BST& bst) {
    BST bst1(bst);
    this->~BST();
    this->root = bst1.root;
    return *this;
}

BST& BST::operator=(BST&& src) {
    this->~BST();
    this->root = src.root;
    return *this;
}

BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for(auto& node: nodes)
        delete node;
}

