#include <iostream>
#include <vector>
#include <map>
#include <utility>

template <typename T> T Sqr(T val);
template<typename K, typename V> std::pair<K, V> Sqr(const std::pair<K, V>& val);
template <typename T> std::vector<T> Sqr(const std::vector<T>& val);
template <typename K, typename V> std::map<K, V> Sqr(const std::map<K, V>& val);

template <typename T>
T Sqr(T val) {
	return val * val;
}

template <typename T>
std::vector<T> Sqr(const std::vector<T>& val) {
	std::vector<T> result;

	for (const auto& i : val) {
		result.push_back(Sqr(i));
	}

	return result;
}

template<typename K, typename V>
std::pair<K, V> Sqr(const std::pair<K, V>& val) {
	return {Sqr(val.first), Sqr(val.second)};
}

template <typename K, typename V>
std::map<K, V> Sqr(const std::map<K, V>& val) {
	std::map<K, V> result;

	for (const auto& item : val) {
		result[item.first] = Sqr(item.second);
	}

	return result;
}

int main() {
	std::vector<int> v = {1, 2, 3};
	std::cout << "vector:";
	for (auto i : Sqr(v)) {
		std::cout << ' ' << i;
	}
	std::cout << std::endl;

	std::map<int, std::pair<int, int>> map_of_pairs = {
		{4, {2, 2}},
		{7, {4, 3}}
	};
	std::cout << "map of pairs:" << std::endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
	}

	return 0;
}
