#include <iostream>
#include <vector>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// int distance = range_end - range_begin;
	int distance = std::distance(range_begin, range_end);
	if (distance < 2) { return; }

	std::vector<typename RandomIt::value_type> vec(range_begin, range_end);
	auto mid_point = vec.begin() + distance/2;

	MergeSort(vec.begin(), mid_point);
	MergeSort(mid_point, vec.end());
	std::merge(vec.begin(), mid_point,
		mid_point, vec.end(), range_begin);
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