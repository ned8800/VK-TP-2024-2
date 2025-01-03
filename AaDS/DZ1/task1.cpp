
// Инвертируйте значение бита в числе N по его номеру K.

// Необходимо использование битовых операций.
// Использование арифметических операций запрещено.
// Формат ввода

// Сначала вводится число N.
// Оно лежит в диапазоне 0..232-1 и вводится в десятичном виде.

// Далее вводится номер бита K.
// Лежит в диапазоне 0..31 и вводится в десятичном виде.

// Выходное число выводится в десятичном виде. 


#include <iostream>

int main() {
    unsigned int N;
    int K;
    std::cin >> N >> K;

    N ^= (1 << K);

    std::cout << N << std::endl;
    return 0;
}
