#include <vector>
#include <iostream>
#include <sstream>
#include <map>

template <typename First, typename Second>
std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p) {
	return out << '(' << p.first << ',' << p.second << ')';
}

template <typename Collection>
std::string join(const Collection& c, char delim) {
	std::stringstream ss;
	bool first = true;
	for (const auto& i : c) {
		if (!first) {
			ss << delim;
		}
		first = false;
		ss << i;
	}
	return ss.str();
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vec) {
	return out << '[' << join(vec, ',') << ']';
}

template <typename Key, typename Val>
std::ostream& operator << (std::ostream& out, const std::map<Key, Val>& m) {
	return out << '{' << join(m, ',') << '}';
}

int main() {
	std::vector<double> vec = {1.0, 2.3, 3.9};
	std::cout << vec << std::endl;

	std::map<int, double> m = {{1, 2.2}, {3, 4.1}};
	std::cout << m << std::endl;
	return 0;
}
