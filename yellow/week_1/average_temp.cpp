#include <iostream>
#include <vector>
#include <limits>

int main() {
	int n;
	std::cin >> n;
	std::vector<int> temperatures(n);
	int64_t sum = 0;
	for (int& temperature : temperatures) {
		std::cin >> temperature;
		sum += temperature;
	}

	int average = sum / n;
	std::vector<int> result_indices;
	for (int i = 0; i < n; ++i) {
		if (temperatures[i] > average) {
			result_indices.push_back(i);
		}
	}

	std::cout << result_indices.size() << std::endl;
	for (int result_index : result_indices) {
		std::cout << result_index << " ";
	}
	std::cout << std::endl;
	return 0;
}
