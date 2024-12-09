/*
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Требования: к дополнительной памяти: O(1). 
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.


Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы.
Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/


#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

template<typename Key>
struct DefaultComparator {
	bool operator()(const Key& left, const Key& right) const {
		return left < right;
	}
};

int randomizer(int l, int r) {
	return trunc(rand() % ((r-1) - l + 1) + l);
}


template <typename Key, typename Comparator = DefaultComparator<Key>>
int partition(Key *arr, int l, int r, Comparator cmp = Comparator()) {
    int pivot_idx = int(randomizer(l ,r));
	
    Key pivot = arr[pivot_idx];
    
	std::swap(arr[pivot_idx], arr[l]);
	
	int i = r-1;
	int j = r-1;
	

    while(j > (l)) {
		if(cmp(arr[j], pivot)) {
			j--;
			if(!cmp(arr[i], pivot)) { i--; }
		}
		else {
			std::swap(arr[j], arr[i]);
			i--;
			j--;
		}
    }
	std::swap(arr[i], arr[l]);
	return i;
}


///////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Comparator = DefaultComparator<Key>>
void kth_stat(Key *arr, int arr_size, int k, Comparator cmp = Comparator()) {
	int left = 0;
	int right = arr_size;
	
	while(left < right) {
		int middle = partition(arr, left, right);
		if(middle == k) {
			return;
		}
		else if(middle < k) {
			left = middle + 1;
		}
		else {
			right = middle;
		}
	}
	
}

int percentil(int percent, int value) {
	return trunc(value * percent / 100);
}


int main() {
	int N = 0;
	cin >> N;
	int tmp = 0;
	vector<int> arr{};
	for(int i = 0; i < N; ++i) {
		cin >> tmp;
		arr.push_back(tmp);
	}
    
	int K10 = int(percentil(10, N));
	int Kmid = percentil(50, N);
	int K90 = percentil(90, N);
	
	kth_stat(&arr[0], arr.size(), K10);
	cout << arr[K10] << endl;
	kth_stat(&arr[0], arr.size(), Kmid);
	cout << arr[Kmid] << endl;
	kth_stat(&arr[0], arr.size(), K90);
	cout << arr[K90] << endl;

    return 0;
}


