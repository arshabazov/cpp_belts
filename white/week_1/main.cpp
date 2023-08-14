#include <iostream>
#include <vector>

bool IsPalindrom(const std::string& str) {
	for (int i = 0; i < str.size()/2; ++i) {
		if (str[i] != str[str.size() - i - 1]) {
			return false;
		}
	}
	return true;
}

std::vector<std::string> PalindromFilter(const std::vector<std::string>& words, int minLength) {
	std::vector<std::string> vec;
	
	for (auto& word: words) {
		if (word.length() >= minLength && IsPalindrom(word)) {
			vec.push_back(word);
		}
	}
	return vec;
}