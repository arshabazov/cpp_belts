#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>

int main() {
	// int n;
	
	// std::cin >> n;
	// std::string str;
	// str.reserve(n);
	// for (int i = 0; i < n; ++i) {
	// 	char c;
	// 	std::cin >> c;
	// 	str.push_back(c);
	// }
	// std::sort(begin(str), end(str), [](char a, char b) {
	// 	return std::tolower(a) < std::tolower(b);
	// });
	
	// for (int i = 0; i < str.size(); ++i) {
	// 	std::cout << str[i] << ' ';
	// }
	// std::cout << std::endl;
	
	int n;
	std::cin >> n;
	std::vector<std::string> v(n);
	for (std::string& s : v) {
		std::cin >> s;
	}
	sort(begin(v), end(v), [](const std::string& l, const std::string& r) {
		return lexicographical_compare(begin(l), end(l), begin(r), end(r),[](char cl, char cr) { 
			return tolower(cl) < tolower(cr); });});
	for (int i = 0; i < v.size(); ++i) {
		std::cout << v[i] << ' ';
	}
	std::cout << std::endl;
	return 0;
}