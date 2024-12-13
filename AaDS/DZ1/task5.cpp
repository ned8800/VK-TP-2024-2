// Требование для всех вариантов Задачи 5
// Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
// Решение должно поддерживать передачу функции сравнения снаружи.
// Общее время работы алгоритма O(n log n).

// 5_2. Современники.
//  Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет. Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.

// Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
// Формат ввода
// Сначала на вход программы поступает число N — количество людей (меньше 10000).
// Далее в N строках вводится по 6 чисел — первые три задают дату (день, месяц, год) рождения, следующие три — дату смерти (она всегда не ранее даты рождения). День (в зависимости от месяца, а в феврале — еще и года) от 1 до 28, 29, 30 или 31, месяц — от 1 до 12, год — от 1 до 2005.
// Формат вывода
// Единственное число – максимальное количество современников. 

#include <iostream>
#include <vector>
#include <map>

struct Date {
    int day, month, year;
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    Date addYears(int years) const {
        return {day, month, year + years};
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::map<Date, int> events;
    
    for (int i = 0; i < n; ++i) {
        Date birth, death;
        std::cin >> birth.day >> birth.month >> birth.year;
        std::cin >> death.day >> death.month >> death.year;
        
        Date start = birth.addYears(18);
        Date end = std::min(death, birth.addYears(80));
        
        if (start < end) {
            events[start] += 1; 
            events[end] -= 1;
        }
    }
    
    int maxCount = 0, currentCount = 0;
    for (const auto& [date, change] : events) {
        currentCount += change;
        maxCount = std::max(maxCount, currentCount);
    }
    
    std::cout << maxCount << std::endl;
    return 0;
}
