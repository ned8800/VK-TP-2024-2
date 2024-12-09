/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. 
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
 когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, 
 удаления строки из множества и проверки принадлежности данной строки множеству.

Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
Вариант 2. Для разрешения коллизий используйте двойное хеширование.
Формат ввода

Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит
 из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции – один из трех символов:
 + означает добавление данной строки в множество;
 - означает удаление строки из множества;
 ? означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат вывода

Программа должна вывести для каждой операции одну из двух строк OK или FAIL.

Для операции '?': OK, если элемент присутствует во множестве. FAIL иначе.

Для операции '+': FAIL, если добавляемый элемент уже присутствует во множестве и потому не может быть добавлен. OK иначе.

Для операции '-': OK, если элемент присутствовал во множестве и успешно удален. FAIL иначе.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

static constexpr int START_HASH_CAPACITY = 8;

static constexpr int HASHER_MULTIPLYER = 7;

static constexpr int ADDITIONAL_HASHER_MULTIPLYER = 11;


struct Hasher {
    Hasher(int _hasherMultiplyer) : hasherMultiplyer(_hasherMultiplyer) {}
    ~Hasher() = default;

    Hasher(const Hasher &) = default;

    Hasher &operator=(const Hasher &) = default;

    unsigned long long operator()(const std::string &key, int mult = HASHER_MULTIPLYER) const {
        unsigned long long hash = 0;
        for (auto &i: key) {
            hash = hash * mult + i;
        }
        return hash;
    }

private:
    int hasherMultiplyer = HASHER_MULTIPLYER;
};

template<class Key, class H>
class HashTable {
public:
    HashTable() = delete;

    HashTable(const H &hasher, Key emptyValue, Key deletedValue) :
            hasher(hasher),
            table(START_HASH_CAPACITY, emptyValue),
            emptyValue(std::move(emptyValue)),
            deletedValue(std::move(deletedValue)),
            size(0) {}

    HashTable(const HashTable &hashTable) : table(hashTable.table), size(hashTable.size),
                                      hasher(hashTable.hasher),
                                      emptyValue(hashTable.emptyValue),
                                      deletedValue(hashTable.deletedValue) {}

    ~HashTable() = default;

    HashTable &operator=(const HashTable &hashTable) {
        table = hashTable.table;
        size = hashTable.size;
        hasher = hashTable.hasher;
        emptyValue = hashTable.emptyValue;
        deletedValue = hashTable.deletedValue;
        return *this;
    }

    bool insert(const Key &key) {
        if(((size*4)/table.size()) >= (3)) { // проверка на заполнение на 3/4
            grow();
        }
        int hash1 = hasher(key) % table.size();
        // второй хеш с значением множителя ADDITIONAL_HASHER_MULTIPLYER
        int mult = (hasher(key, ADDITIONAL_HASHER_MULTIPLYER)*2 + 1) % table.size();
        if (table[hash1] == emptyValue) {
            table[hash1] = key;
            ++size;
            return true;
        }
        if (table[hash1] == key) {
            return false;
        }

        int cellDeletedIdx = -1;
        
        for (int i = 1; i != table.size(); i++) {
            int probeIndex = (hash1 + i * mult) % table.size();
            if (table[probeIndex] == key) {
                return false;
            }
            if (table[probeIndex] == emptyValue) {
                table[probeIndex] = key;
                ++size;
                return true;
            }
            if ((table[probeIndex] == deletedValue) && (cellDeletedIdx == -1)) {
                cellDeletedIdx = probeIndex;                
            }
        }

        if (cellDeletedIdx != -1) {
            table[cellDeletedIdx] = key;
            ++size;
            return true;
        }

        return false;
    }

    bool contains(const Key &key) {
        int hash1 = hasher(key) % table.size();
        int mult = (hasher(key, 11)*2 + 1) % table.size();
        if (table[hash1] == key) {
            return true;
        }
        if (table[hash1] == emptyValue) {
            return false;
        }
        for (int i = 1; i != table.size(); ++i) {
            int probeIndex = (hash1 + i * mult) % table.size();
            if (table[probeIndex] == key) {
                return true;
            }
            if (table[probeIndex] == emptyValue) {
                return false;
            }
        }
        return false;
    }

    bool remove(const Key &key) {
        int hash1 = hasher(key) % table.size();
        int mult = (hasher(key, 11)*2 + 1) % table.size();
        if (table[hash1] == key) {
            table[hash1] = deletedValue;
            --size;
            return true;
        }
        if (table[hash1] == emptyValue) {
            return false;
        }
        for (int i = 1; i != table.size(); ++i) {
            int probeIndex = (hash1 + i * mult) % table.size();
            if (table[probeIndex] == key) {
                table[probeIndex] = deletedValue;
                --size;
                return true;
            }
            if (table[probeIndex] == emptyValue) {
                return false;
            }
        }
        return false;
    }

private:
    std::vector<Key> table;
    int size = 0;
    H hasher;
    Key emptyValue;
    Key deletedValue;

    void grow() {
        std::vector<Key> newTable(table.size() * 2, emptyValue);
        std::vector<Key> oldTable = std::move(table);
        table = std::move(newTable);
        for (const auto &key: oldTable) {
            if (key != emptyValue && key != deletedValue) {
                insert(key);
            }
        }
    }
};



int main() {
    HashTable<std::string, Hasher> table(Hasher(HASHER_MULTIPLYER),
                                         "\a", "\b");
    char operation = '0';
    std::string key;

    while(std::cin >> operation >> key) {
        bool result = false;
        switch (operation) {
            case '+':
                result = table.insert(key);
                break;
            case '-':
                result = table.remove(key);
                break;
            case '?':
                result = (table.contains(key));
                break;
            case '#':
                return 0;
            default:

                return 1;
        }
        if (result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }

    return 0;
}






// int main() {
//     HashTable<std::string, Hasher> table(Hasher(HASHER_MULTIPLYER),
//                                          "\a", "\b");
//     char operation = '0';
//     std::string key;

    
//     std::ifstream in;          // поток для записи
//     in.open("/home/ned8800/Study/Technopark 2024-2/АиСД/AlgorythmsAndDataStructures2024-2/DZ2/task1_data/006.txt");      // открываем файл для записи
    
//     std::ofstream out;          // поток для записи
//     out.open("answer.txt");      // открываем файл для записи
//     if ((in.is_open()) && (out.is_open())) {
//         std::cout << "yes" << '\n';

//         while(in >> operation >> key) {
//             bool result = false;
//             switch (operation) {
//                 case '+':
//                     result = table.insert(key);
//                     break;
//                 case '-':
//                     result = table.remove(key);
//                     break;
//                 case '?':
//                     result = (table.contains(key));
//                     break;
//                 case '#':
//                     in.close();
//                     out.close();
//                     return 0;
//                 default:
//                     in.close();
//                     out.close();
//                     return 1;
//             }
//             if (result) {
//                 out << "OK" << std::endl;
//             } else {
//                 out << "FAIL" << std::endl;
//             }
//         }
//     }
//     in.close();
//     out.close();

//     return 0;
// }
