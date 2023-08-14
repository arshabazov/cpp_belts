#include <iostream>
#include <set>
#include <map>

int main() {
	std::map<std::string, std::set<std::string> > synonym_dict;
	int n;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::string command;
		
		std::cin >> command;
		if (command == "ADD") {
			std::string word1, word2;
			std::cin >> word1 >> word2;
			synonym_dict[word1].insert(word2);
			synonym_dict[word2].insert(word1);
		} else if (command == "COUNT") {
			std::string word;
			std::cin >> word;
			std::cout << synonym_dict[word].size() << std::endl;
		} else if (command == "CHECK") {
			std::string word1, word2;
			std::cin >> word1 >> word2;
			if (synonym_dict[word1].count(word2) == 1) {
				std::cout << "YES" << std::endl;
			} else {
				std::cout << "NO" << std::endl;
			}
		}
	}
	return 0;
}