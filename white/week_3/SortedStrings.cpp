#include <iostream>
#include <vector>
#include <algorithm>

class SortedStrings {
public:
	void AddString(const std::string& s) {
		// добавить строку s в набор
		strs.push_back(s);
	}
	
	std::vector<std::string> GetSortedStrings() {
		// получить набор из всех добавленных строк в отсортированном порядке
		std::sort(begin(strs), end(strs));
		return strs;
	}
	
private:
	// приватные поля
	std::vector<std::string> strs;
};

void PrintSortedStrings(SortedStrings& strings) {
	for (const std::string& s : strings.GetSortedStrings()) {
		std::cout << s << " ";
	}
	std::cout << std::endl;
}

int main() {
	SortedStrings strings;
	
	strings.AddString("first");
	strings.AddString("third");
	strings.AddString("second");
	PrintSortedStrings(strings);
	
	strings.AddString("second");
	PrintSortedStrings(strings);
	
	return 0;
}
