/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).

Формат ввода
В первой строке записано число N.
Во последующих N строках — целые числа исходной последовательности.

Формат вывода
N целых чисел, разделенных пробелом. 
*/

#include <iostream>
#include <queue>
#include <vector>

template<class T>
struct BinTreeNode {
    BinTreeNode(const T &element) : data(element), left(nullptr), right(nullptr) {};

    T data;
    BinTreeNode *left = nullptr;
    BinTreeNode *right = nullptr;
};

template<class T>
class BinTree {
public:
    BinTree() : root(nullptr) {}
    // для задачи не имеет смысла реализовывать 2 оставшихся конструктора,
    // поэтому я и не стал

    ~BinTree() {
        std::queue<BinTreeNode<T> *> queueToDeleteElements;
        queueToDeleteElements.push(root);
        while (!queueToDeleteElements.empty()) {
            BinTreeNode<T> *current = queueToDeleteElements.front();
            if (current->left) {
                queueToDeleteElements.push(current->left);
            }
            if (current->right) {
                queueToDeleteElements.push(current->right);
            }
            delete current;
            queueToDeleteElements.pop();
        }
    }

    void add(const T &element) {
        if (root == nullptr) {
            root = new BinTreeNode(element);
            return;
        } 

        BinTreeNode<T> *treeNode = root;
        while (true) {
            if (treeNode->data <= element) {
                if (treeNode->right == nullptr) {
                    treeNode->right = new BinTreeNode(element);
                    break;
                }
                treeNode = treeNode->right;
            } else {
                if (treeNode->left == nullptr) {
                    treeNode->left = new BinTreeNode(element);
                    break;
                }
                treeNode = treeNode->left;
            }
        }
        return;
    }


    std::queue<T> extractAllLevelOrder() {
        std::queue<T> tempQueue;
        if (!root) {
            return tempQueue;
        }
        
        std::queue<BinTreeNode<T> *> binNodeQueue;
        binNodeQueue.push(root);
        while (!binNodeQueue.empty()) {
            BinTreeNode<T> *node = binNodeQueue.front();
            binNodeQueue.pop();
            tempQueue.push(node->data);
            if (node->left) {
                binNodeQueue.push(node->left);
            }
            if (node->right) {
                binNodeQueue.push(node->right);
            }
        }
        return tempQueue;
    }

private:
    BinTreeNode<T> *root = nullptr;
};


int main() {
    size_t count = 0;
    std::cin >> count;
    BinTree<int> binTree;
    int element = 0;
    for (size_t i = 0; i < count; i++) {
        std::cin >> element;
        binTree.add(element);
    }
    std::queue<int> queue = binTree.extractAllLevelOrder();
    while (!queue.empty()) {
        std::cout << queue.front() << ' ';
        queue.pop();
    }
    return 0;
}
