#include <iostream>
#include <vector>

template <class Key>
struct Comparator {
    int operator()(const Key &a, const Key &b) const {
        if (a < b) { 
            return -1;
        }
        return a > b;
    }
};

template <class Key, class Comparator = Comparator<Key>>
class AVLTree {
    struct Node {
        Key key;
        Node *left;
        Node *right;
        size_t height;
        size_t nodeSize;

        Node(const Key &key) : key(key), left(nullptr), right(nullptr), height(1), nodeSize(1) {}
    };

public:
    AVLTree(Comparator comparator = Comparator()) : comparator(comparator), root(nullptr) {}
    ~AVLTree() { deleteNode(root); }

    int insert(const Key &key) {
        int position = 0;
        root = insertNode(root, key, position);
        return position;
    }

    void erase(size_t index) {
        root = eraseNodeByIndex(root, index);
    }

private:
    Node *insertNode(Node *node, const Key &key, int &position) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (comparator(key, node->key) == -1) {
            position += getNodeSize(node->left) + 1;
            node->right = insertNode(node->right, key, position);
        } else {
            node->left = insertNode(node->left, key, position);
        }
        return balanceTree(node);
    }

    Node *eraseNodeByIndex(Node *node, size_t index) {
        if (!node) {
            return nullptr;
        }
        size_t leftSize = getNodeSize(node->left);
        if (index < leftSize) {
            node->left = eraseNodeByIndex(node->left, index);
        } else if (index > leftSize) {
            node->right = eraseNodeByIndex(node->right, index - leftSize - 1);
        } else {
            Node *left = node->left, *right = node->right;
            delete node;
            if (!right) return left;
            Node *minRight;
            right = removeMinNode(right, minRight);
            minRight->left = left;
            minRight->right = right;
            return balanceTree(minRight);
        }
        return balanceTree(node);
    }

    Node *rotateLeft(Node *node) {
        Node *right = node->right;
        node->right = right->left;
        right->left = node;
        fixFields(node);
        fixFields(right);
        return right;
    }

    Node *rotateRight(Node *node) {
        Node *left = node->left;
        node->left = left->right;
        left->right = node;
        fixFields(node);
        fixFields(left);
        return left;
    }

    Node *balanceTree(Node *node) {
        fixFields(node);
        int balanceFactor = getNodeHeight(node->right) - getNodeHeight(node->left);
        if (balanceFactor == 2) {
            if (getNodeHeight(node->right->right) < getNodeHeight(node->right->left)) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        if (balanceFactor == -2) {
            if (getNodeHeight(node->left->left) < getNodeHeight(node->left->right)) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        return node;
    }

    Node *removeMinNode(Node *node, Node *&min) {
        if (!node->left) {
            min = node;
            return node->right;
        }
        node->left = removeMinNode(node->left, min);
        return balanceTree(node);
    }

    size_t getNodeHeight(Node *node) const {
        return node ? node->height : 0;
    }

    void fixFields(Node *node) {
        node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
        node->nodeSize = 1 + getNodeSize(node->left) + getNodeSize(node->right);
    }

    size_t getNodeSize(Node *node) const {
        return node ? node->nodeSize : 0;
    }

    void deleteNode(Node *node) {
        if (node) {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    }

    Comparator comparator;
    Node *root;
};

int main() {
    int N;
    std::cin >> N;

    AVLTree<int> tree;
    for (int i = 0; i < N; ++i) {
        int command, value;
        std::cin >> command >> value;
        if (command == 1) {
            int position = tree.insert(value);
            std::cout << position << '\n';
        } else if (command == 2) {
            tree.erase(value);
        }
    }

    return 0;
}
