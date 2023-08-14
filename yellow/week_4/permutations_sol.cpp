#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


int main() {
	int range_length;
	std::cin >> range_length;
	std::vector<int> permutation(range_length);

	// iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
	// Заполняет диапазон последовательно возрастающими значениями
	// Обратные итераторы позволяют заполнить его, двигаясь от конца к началу
	iota(permutation.rbegin(), permutation.rend(), 1); 

	// prev_permutation ->
	//     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
	// Преобразует диапазон в предыдущую (лексикографически) перестановку,
	// если она существует, и возвращает true,
	// иначе (если не существует) - в последнюю (наибольшую) и возвращает false
	do {
	  for (int num : permutation) {
	    std::cout << num << ' ';
	  }
	  std::cout << std::endl;
	} while (std::prev_permutation(permutation.begin(), permutation.end()));	
	return 0;
}
