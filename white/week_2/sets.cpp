#include <set>
#include <iostream>
#include <map>

std::set<std::string> BuildMapValuesSet(std::map<int, std::string> m) {
	std::set<std::string> values;
	
	for (auto& item : m) {
		values.insert(item.second);
	}
	
	return values;
}

int main() {
	std::set<std::string> values = BuildMapValuesSet({
		{1, "odd"},
		{2, "even"},
		{3, "odd"},
		{4, "even"},
		{5, "odd"}
	});
	for (const std::string& value : values) {
		std::cout << value << std::endl;
	}
	
	return 0;
}