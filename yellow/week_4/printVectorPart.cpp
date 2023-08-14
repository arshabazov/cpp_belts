#include <vector>
#include <iostream>
#include <algorithm>

void PrintVectorPart(const std::vector<int>& numbers) {
	const auto negative = std::find_if(numbers.begin(), numbers.end(),
		[](int n) {
			return n < 0;
	});
	for (auto it = negative; it != numbers.begin(); ) {
		std::cout << *(--it) << " ";
	}
}

int main() {
	PrintVectorPart({6, 1, 8, -5, 4});
	std::cout << std::endl;
	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	std::cout << std::endl;
	PrintVectorPart({6, 1, 8, 5, 4});
	std::cout << std::endl;

	return 0;
}