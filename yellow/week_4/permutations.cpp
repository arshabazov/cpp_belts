#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void printVec(const std::vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i];
	}
}

int main() {
	int n;
	std::cin >> n;
	std::vector<int> vec(n);
	for (int i = 0; i < n; ++i) {
		vec[i] = n - i;
	}

	do {
		for (int i : vec) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	} while (std::prev_permutation(vec.begin(), vec.end()));
	
	return 0;
}