#include <algorithm>
// #include <iostream>
#include "sum_reverse_sort.h"

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	std::reverse(s.begin(), s.end());

	return s;
}

void Sort(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
}

// int main() {
// 	int sum = Sum(2, 3);
// 	std::cout << "sum = " << sum << std::endl;

// 	std::string str = Reverse("hello");
// 	std::cout << "string = " << str << std::endl;

// 	std::vector<int> v = {4, 1, 3, 2};
// 	Sort(v);
// 	for (int i = 0; i < v.size(); ++i) {
// 		std::cout << v[i];
// 	}
// 	std::cout << std::endl;

// 	return 0;
// }