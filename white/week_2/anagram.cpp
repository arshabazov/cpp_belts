#include <iostream>
#include <map>

std::map<char, int> BuildCharCounters(const std::string& word) {
	std::map<char, int> char_map;
	
	for (int i = 0; i < word.size(); ++i) {
		++char_map[word[i]];
	}
	
	return char_map;
}

int main() {
	std::string word1, word2;
	int n;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> word1 >> word2;
		std::map<char, int> map1 = BuildCharCounters(word1);
		std::map<char, int> map2 = BuildCharCounters(word2);
		if (map1 == map2) {
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
		}
	}
	
	return 0;
}