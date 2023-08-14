#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
	std::vector<T> vec;
	auto border_it = std::find_if(elements.begin(), elements.end(),
		[border](const T& element){
			return element > border;
		}
	);
	for (auto it = border_it; it != elements.end(); ++it) {
		vec.push_back(*it);
	}
	return vec;
}

int main() {
	for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
	  std::cout << x << " ";
	}
	std::cout << std::endl;

	std::string to_find = "Python";
	std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"},
		to_find).size() << std::endl;
	return 0;
}