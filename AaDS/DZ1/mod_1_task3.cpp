// Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
// Формат входных данных.
// В первой строке количество команд n. n ≤ 1000000.
// Каждая команда задаётся как 2 целых числа: a b.
// a = 1 - push front
// a = 2 - pop front
// a = 3 - push back
// a = 4 - pop back
// Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
// Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
// Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
// Формат выходных данных.
// Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

// 3_1. Реализовать очередь с динамическим зацикленным буфером (на основе динамического массива).
// Требования: Очередь должна быть реализована в виде класса.
 

#include <iostream>
#include <vector>

class MyDeque {
public:
    MyDeque() : data(4), head(0), tail(0), size(0) {}

    void pushFront(int value) {
        resize();
        head = (head - 1 + data.size()) % data.size();
        data[head] = value;
        size++;
    }

    int popFront() {
        if (size == 0) return -1;
        int result = data[head];
        head = (head + 1) % data.size();
        size--;
        return result;
    }

    void pushBack(int value) {
        resize();
        data[tail] = value;
        tail = (tail + 1) % data.size();
        size++;
    }

    int popBack() {
        if (size == 0) return -1;
        tail = (tail - 1 + data.size()) % data.size();
        int result = data[tail];
        size--;
        return result;
    }

private:
    std::vector<int> data;
    int head, tail, size;

    void resize() {
        if (size < data.size()) return;
        std::vector<int> newData(data.size() * 2);
        for (int i = 0; i < size; ++i) {
            newData[i] = data[(head + i) % data.size()];
        }
        data = std::move(newData);
        head = 0;
        tail = size;
    }
};

int main() {
    int n;
    MyDeque deque;
    bool isCorrect = true;

    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int command, expected_value;
        std::cin >> command >> expected_value;
        
        int result = 0;
        switch (command) {
            case 1:  // push Front
                deque.pushFront(expected_value);
                break;
            case 2:  // pop Front
                result = deque.popFront();
                if (result != expected_value) {
                    isCorrect = false;
                }
                break;
            case 3:  // push Back
                deque.pushBack(expected_value);
                break;
            case 4:  // pop Back
                result = deque.popBack();
                if (result != expected_value) {
                    isCorrect = false;
                }
                break;
            default:
                isCorrect = false;
                break;
        }

        if (!isCorrect) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }

    std::cout << "YES" << std::endl;
    return 0;
}
