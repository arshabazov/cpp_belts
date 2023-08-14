#pragma once

#include <string>
#include <map>
#include <set>

using Synonyms = std::map<std::string, std::set<std::string>>;

void addSynonyms(Synonyms& synonyms,
	const std::string& first_word, const std::string& second_word);
int getSynonymsCount(Synonyms& synonyms, const std::string& word);
bool areSynonyms(Synonyms& synonyms,
	const std::string& first_word, const std::string& second_word);