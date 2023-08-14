#include <iostream>
#include <vector>
#include <algorithm>

// 1. Если диапазон содержит меньше 2 элементов, выйти из функции.
// 2. Создать вектор, содержащий все элементы текущего диапазона.
// 3. Разбить вектор на 3 равные части.
// 4. Вызвать функцию MergeSort от каждой части вектора.
// 5. Слить первые две трети вектора с помощью алгоритма merge,
//    сохранив результат во временный вектор с помощью back_inserter.
// 6. Слить временный вектор из предыдущего пункта с последней третью вектора
//    из п. 2, записав полученный отсортированный диапазон вместо исходного.

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int distance = range_end - range_begin;
	if (distance < 2) {
	  return;
	}

	std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
	std::vector<typename RandomIt::value_type> temp;

	auto one_third = elements.begin() + distance/3;
	auto two_third = one_third + distance/3;

	MergeSort(elements.begin(), one_third);
	MergeSort(one_third, two_third);
	MergeSort(two_third, elements.end());

	std::merge(elements.begin(), one_third,
		one_third, two_third, std::back_inserter(temp));
	
	std::merge(temp.begin(), temp.end(),
		two_third, elements.end(), range_begin);

	/*
	std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto mid_point = elements.begin() + distance/2;

	MergeSort(elements.begin(), mid_point);
	MergeSort(mid_point, elements.end());
	std::merge(elements.begin(), mid_point,
		mid_point, elements.end(), range_begin);
	*/
}

int main() {
	std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
	
	MergeSort(begin(v), end(v));
	for (int x : v) {
	  std::cout << x << " ";
	}
	std::cout << std::endl;
	
	return 0;
}