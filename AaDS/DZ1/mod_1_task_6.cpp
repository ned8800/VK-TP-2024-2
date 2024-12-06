#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

template<typename T>
struct DefaultComparator {
	bool operator()(const T& left, const T& right) const {
		return left < right;
	}
};

int randomizer(int l, int r) {
	return trunc(rand() % ((r-1) - l + 1) + l);
}

// template <typename T, typename Comparator = DefaultComparator<T>>
// int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
//     int pivot_idx = int(randomizer(l ,r));
	
//     T pivot = arr[pivot_idx];
    
// 	std::swap(arr[pivot_idx], arr[r - 1]);
	
// 	int i = l;
// 	int j = l;
	
//     while(j < (r-1)) {
// 		if(cmp(pivot, arr[j])) {
// 			j++;
// 			if(!cmp(pivot, arr[i])) { i++; }
// 		}
// 		else {
// 			std::swap(arr[i], arr[j]);
// 			i++;
// 			j++;
// 		}
//     }
// 	std::swap(arr[i], arr[r - 1]);
// 	return i;
// }


template <typename T, typename Comparator = DefaultComparator<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
    int pivot_idx = int(randomizer(l ,r));
	
    T pivot = arr[pivot_idx];
    
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
template <typename T, typename Comparator = DefaultComparator<T>>
void kth_stat(T *arr, int arr_size, int k, Comparator cmp = Comparator()) {
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
