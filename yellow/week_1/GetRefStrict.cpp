#include <iostream>
#include <map>
#include <algorithm>
#include <stdexcept>

template <typename K, typename V>
V& GetRefStrict(std::map<K, V>& m, const K& key) {
	if (m.count(key) == 0) {
		throw std::runtime_error("Key not found");
	}
	return m[key];
}

int main() {
	std::map<int, std::string> m = {{0, "value"}};
	std::string& item = GetRefStrict(m, 0);
	std::cout << item << std::endl;
	std::cout << m[0] << std::endl; // выведет newvalue

	return 0;
}
