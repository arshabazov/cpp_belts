#include <iostream>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// 1. Если диапазон содержит меньше 2 элементов, выходим из функции
	int range_length = range_end - range_begin;
	if (range_length < 2) {
	  return;
	}

	// 2. Создаем вектор, содержащий все элементы текущего диапазона
	std::vector<typename RandomIt::value_type> elements(range_begin, range_end);

	// 3. Разбиваем вектор на две равные части
	auto mid = elements.begin() + range_length / 2;

	// 4. Вызываем функцию MergeSort от каждой половины вектора
	MergeSort(elements.begin(), mid);
	MergeSort(mid, elements.end());

	// 5. С помощью алгоритма merge сливаем отсортированные половины
	// в исходный диапазон
	// merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
	std::merge(elements.begin(), mid, mid, elements.end(), range_begin);
}

int main() {
	std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	
	// MergeSort(begin(v), end(v));
	MergeSort(v.begin(), v.end());
	for (int x : v) {
	  std::cout << x << " ";
	}
	std::cout << std::endl;
	
	return 0;
}