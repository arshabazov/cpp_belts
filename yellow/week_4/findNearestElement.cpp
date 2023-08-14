#include <iostream>
#include <set>
#include <iterator>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers,
	int border)
{
	const auto it = numbers.lower_bound(border);
	if (it == numbers.begin()) {
		return it;
	}
	const auto prev = std::prev(it);
	if (it == numbers.end()) {
		return prev;
	}
	int a = *it - border;
	int b = border - *prev;
	if (b <= a) {
		return prev;
	}
	
	return it;
}

int main() {
	std::set<int> numbers = {1, 4, 6};

	std::cout <<
		*FindNearestElement(numbers, 0) << " " <<
		*FindNearestElement(numbers, 3) << " " <<
		*FindNearestElement(numbers, 5) << " " <<
		*FindNearestElement(numbers, 6) << " " <<
		*FindNearestElement(numbers, 100) << std::endl;
	
	std::set<int> empty_set;

	std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
	return 0;
}