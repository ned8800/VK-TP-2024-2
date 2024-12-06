// Требование для всех вариантов Задачи 4
// Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса. 
// Решение должно поддерживать передачу функции сравнения снаружи.
// Куча должна быть динамической.

// 4.1 Слияние массивов.
// Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
// Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
// Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.
// Формат выходных данных: Итоговый отсортированный массив.

#include <iostream>
#include <functional>
#include <vector>

struct Element {
    int value;
    int arrayIndex;
    int elementIndex;

    Element() : value(0), arrayIndex(0), elementIndex(0) {}  // Конструктор по умолчанию
    Element(int v, int arrayInd, int elemInd) : value(v), arrayIndex(arrayInd), elementIndex(elemInd) {}
};

struct Comparator {
    bool operator()(const Element& a, const Element& b) {
        return a.value > b.value;
    }
};

template <typename T, typename Compare>
class MyHeap {
public:
    MyHeap(Compare comp) : comp(comp), capacity(4), size(0) {
        innerHeap = new T[capacity];
    }

    ~MyHeap() {
        delete[] innerHeap;
    }

    void push(const T& value) {
        if (size == capacity) {
            resize();
        }
        innerHeap[size] = value;
        siftUp(size);
        size++;
    }

    T pop() {
        T top = innerHeap[0];
        innerHeap[0] = innerHeap[size-1];
        size -= 1;
        siftDown(0);
        return top;
    }

    bool isEmpty() const {
        return (size == 0);
    }

private:
    T* innerHeap;
    Comparator comp;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        T* newHeap = new T[capacity];
        for (int i = 0; i < size; ++i) {
            newHeap[i] = innerHeap[i];
        }
        delete[] innerHeap;
        innerHeap = newHeap;
    }

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (comp(innerHeap[parent], innerHeap[index])) {
                std::swap(innerHeap[parent], innerHeap[index]);
                index = parent;

            } else {
                break;
            }
        }
    }

    void siftDown(int index) {
        while (2 * index + 1 < size) {
            int childLeft = 2 * index + 1;
            int childRight = 2 * index + 2;
            int minElem = index;

            if (childLeft < size && comp(innerHeap[minElem], innerHeap[childLeft])) {
                minElem = childLeft;
            }
            if (childRight < size && comp(innerHeap[minElem], innerHeap[childRight])) {
                minElem = childRight;
            }

            if (minElem != index) {
                std::swap(innerHeap[index], innerHeap[minElem]);
                index = minElem;
            } else {
                break;
            }
        }
    }
};

int main() {
    int K;
    std::cin >> K;
    std::vector<std::vector<int>> arrays(K);

    for (int i = 0; i < K; ++i) {
        int size;
        std::cin >> size;
        for (int j = 0; j < size; ++j) {
            int val;
            std::cin >> val;
            arrays[i].push_back(val);
        }
    }

    Comparator COMP;
    MyHeap<Element, Comparator> newHeap(COMP);

    // Инициализирую кучу первыми элементами каждого массива
    for (int i = 0; i < K; ++i) {
        if (!arrays[i].empty()) {
            newHeap.push(Element(arrays[i][0], i, 0));
        }
    }

    std::vector<int> result;

    while (!newHeap.isEmpty()) {
        Element minElement = newHeap.pop();
        result.push_back(minElement.value);

        int nextIndex = minElement.elementIndex + 1;
        if (nextIndex < arrays[minElement.arrayIndex].size()) {
            newHeap.push(Element(arrays[minElement.arrayIndex][nextIndex], minElement.arrayIndex, nextIndex));
        }
    }

    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
