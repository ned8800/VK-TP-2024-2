// 2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m). 
// Требования:  Время работы O(log m). Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.


#include <iostream>
#include <vector>

int findPeakIndex(const std::vector<int>& A) {
    int n = A.size();
    if (n == 1) return 0;

    // Этап экспоненциального поиска
    int bound = 1;
    while (bound < n && A[bound] > A[bound - 1]) {
        bound *= 2;
    }
    
    int leftBound = bound / 2;
    int rightBound = std::min(bound, n - 1);

    // Этап бинарного поиска
    while (leftBound < rightBound) {
        int mid = leftBound + (rightBound - leftBound) / 2;
        if (A[mid] > A[mid + 1]) {
            rightBound = mid;
        } else {
            leftBound = mid + 1;
        }
    }

    return leftBound;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> A[i];
    }

    int m = findPeakIndex(A);
    std::cout << m << std::endl;

    return 0;
}
