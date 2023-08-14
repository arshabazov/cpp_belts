#include "synonyms.h"

void addSynonyms(Synonyms& synonyms,
	const std::string& first_word, const std::string& second_word)
{
	synonyms[first_word].insert(second_word);
	synonyms[second_word].insert(first_word);
}

int getSynonymsCount(Synonyms& synonyms, const std::string& word) {
	return synonyms[word].size();
}

bool areSynonyms(Synonyms& synonyms,
	const std::string& first_word, const std::string& second_word)
{
	return synonyms[first_word].count(second_word) == 1;
}