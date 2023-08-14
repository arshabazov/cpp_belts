#include "tests.h"
#include "synonyms.h"

int main() {
	testAll();
	
	int n;
	Synonyms synonyms;
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		std::string operation_code;
		std::cin >> operation_code;
	
		if (operation_code == "ADD") {
			std::string first_word, second_word;
			std::cin >> first_word >> second_word;
			addSynonyms(synonyms, first_word, second_word);
		} else if (operation_code == "COUNT") {
			std::string word;
			std::cin >> word;
			std::cout << getSynonymsCount(synonyms, word) << std::endl;
		} else if (operation_code == "CHECK") {
			std::string first_word, second_word;
			std::cin >> first_word >> second_word;
			if (areSynonyms(synonyms, first_word, second_word)) {
				std::cout << "YES" << std::endl;
			} else {
				std::cout << "NO" << std::endl;
			}
		}
	}

	return 0;
}