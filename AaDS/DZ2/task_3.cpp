// Постройте B-дерево минимального порядка t и выведите его по слоям.
// В качестве ключа используются числа, лежащие в диапазоне 0..2^32 - 1 -- unsigned int
// Требования:
// B-дерево должно быть реализовано в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.

// Формат входных данных
// Сначала вводится минимальный порядок дерева t.
// Затем вводятся элементы дерева.

// Формат выходных данных
// Программа должна вывести B-дерево по слоям.
// Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct ComparatorUnsInteger {
    bool operator()(unsigned int a, unsigned int b) const {
        return (a < b);
    }
};

template<typename Key, typename Comparator>
class BTree {
public:
    BTree(size_t minimalOrder, Comparator comp) : root(nullptr), nodeMinimalOrder(minimalOrder), comparator(comp) {}

    ~BTree() {
        delete root;
    }

    void add(const Key &key) {
        if (root == nullptr) {
            root = new Node(true);
        }

        if (isNodeFull(root)) {
            Node *newRoot = new Node(false);
            newRoot->childNodes.push_back(root);
            root = newRoot;
            splitNode(root, 0);
        }

        addKeyToNode(root, key);
    }

    void printLevelOrder(std::ostream &out) {
        std::vector<std::vector<Key>> treeLevels;
        traverse(root, 0, treeLevels);
        for (const auto &layer: treeLevels) {
            for (const auto &key: layer) {
                out << key << ' ';
            }
            out << '\n';
        }
    }


private:
    struct Node {
        bool isLeaf;
        std::vector<Key> keys;
        std::vector<Node *> childNodes;

        Node(bool isLeaf) : isLeaf(isLeaf) {}

        ~Node() {
            for (Node *child: childNodes) {
                delete child;
            }
        }
    };

    Node *root;
    size_t nodeMinimalOrder;
    Comparator comparator;

    void traverse(Node *node, int depth, std::vector<std::vector<Key>> &treeLevels) {
        if (treeLevels.size() <= depth) {
            treeLevels.resize(depth + 1);
        }
        treeLevels[depth].insert(treeLevels[depth].end(), node->keys.begin(), node->keys.end());
        for (auto child: node->childNodes) {
            traverse(child, depth + 1, treeLevels);
        }
    }

    bool isNodeFull(Node *node) const {
        return (node->keys.size() == 2 * nodeMinimalOrder - 1);
    }

    void addKeyToNode(Node *node, const Key &key)  {
        if (node->isLeaf) {
            node->keys.push_back(key);
            std::sort(node->keys.begin(), node->keys.end(), comparator);
        } else {
            int position = (node->keys.size() - 1);

            while (comparator(key, node->keys[position]) && position > -1) {
                position--;
            }
            if (isNodeFull(node->childNodes[position + 1])) {
                splitNode(node, position + 1);
                if (comparator(node->keys[position + 1], key)) {
                    ++position;
                }
            }
            addKeyToNode(node->childNodes[position + 1], key);
        }
    }

    void splitNode(Node *node, int position) {
        Node *child = node->childNodes[position];
        int mid = child->keys.size() / 2;

        Node *right = new Node(child->isLeaf);
        right->keys.insert(right->keys.end(), child->keys.begin() + mid + 1, child->keys.end());
        child->keys.resize(mid);

        if (!child->isLeaf) {
            right->childNodes.insert(right->childNodes.end(), child->childNodes.begin() + mid + 1, child->childNodes.end());
            child->childNodes.resize(mid + 1);
        }

        node->keys.insert(node->keys.begin() + position, child->keys[mid]);
        node->childNodes.insert(node->childNodes.begin() + position + 1, right);
    }
};

void solution() {
    size_t neededOrder;
    unsigned int key;
    ComparatorUnsInteger uIntComparator;
    
    std::cin >> neededOrder;
    BTree<unsigned int, ComparatorUnsInteger> tree(neededOrder, uIntComparator);
    
    while (std::cin >> key) {
        tree.add(key);
    }

    tree.printLevelOrder(std::cout);
}

int main() {
    solution();
    return 0;
}
