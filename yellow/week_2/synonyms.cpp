#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include <exception>
#include <sstream>

using Synonyms = std::map<std::string, std::set<std::string>>;

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
  return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	
	return os << "}";
}

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

template <typename T, typename U>
void assertEqual(const T& t, const U& u, const std::string& hint) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) {
	assertEqual(b, true, hint);
}

void testAddSynonyms() {
	{
		Synonyms empty;
		addSynonyms(empty, "a", "b");
		const Synonyms expected = {
			{"a", {"b"}},
			{"b", {"a"}}
		};
		assertEqual(empty, expected, "adding synonyms a and b to an empty set");
	}
	{
		Synonyms synonyms = {
			{"a", {"b"}},
			{"b", {"a", "c"}},
			{"c", {"b"}}
		};
		addSynonyms(synonyms, "a", "c");
		const Synonyms expected = {
			{"a", {"b", "c"}},
			{"b", {"a", "c"}},
			{"c", {"b", "a"}}
		};
		assertEqual(synonyms, expected, "adding synonyms a and c to a set");
	}
}

void testGetSynonymsCount() {
	{
		Synonyms empty;
		assertEqual(getSynonymsCount(empty, "a"), 0, "Count synonyms for an empty set");
	}
	{
		Synonyms synonyms = {
			{"a", {"b", "c"}},
			{"b", {"a"}},
			{"c", {"a"}}
		};
		assertEqual(getSynonymsCount(synonyms, "a"), 2, "Count 2 synonyms for a");
		assertEqual(getSynonymsCount(synonyms, "b"), 1, "Count 1 synonym for b");
		assertEqual(getSynonymsCount(synonyms, "z"), 0, "Count 0 synonyms for z");
	}
}

void testAreSynonyms() {
	{
		Synonyms empty;
		Assert(!areSynonyms(empty, "a" ,"b"), "Are a b synonyms in an empty set");
		Assert(!areSynonyms(empty, "b", "a"), "Are b a synonyms in an empty set");
	}
	{
		Synonyms synonyms = {
			{"a", {"b", "c"}},
			{"b", {"a"}},
			{"c", {"a"}}
		};
		Assert(areSynonyms(synonyms, "a", "b"), "Are a and b synonyms");
		Assert(areSynonyms(synonyms, "b", "a"), "Are b and a synonyms");
		Assert(areSynonyms(synonyms, "a", "c"), "Are a and c synonyms");
		Assert(areSynonyms(synonyms, "c", "a"), "Are c and a synonyms");
		Assert(!areSynonyms(synonyms, "b", "c"), "Are b and c synonyms");
		Assert(!areSynonyms(synonyms, "c", "b"), "Are c and b synonyms");
	}
}

class TestRunner {
private:
	int fail_counter = 0;
public:
	template <typename TestFunc>
	void runTest(TestFunc func, const std::string& test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		} catch (std::runtime_error& e) {
			++fail_counter;
			std::cerr << test_name << " failed: " << e.what() << std::endl;
		}
	}

	~TestRunner() {
		if (fail_counter > 0) {
			std::cerr << "Tests failed: " << fail_counter
			<< " Terminating" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
};

void testAll() {
	TestRunner tester;
	tester.runTest(testAddSynonyms, "testAddSynonyms");
	tester.runTest(testGetSynonymsCount, "testGetSynonymsCount");
	tester.runTest(testAreSynonyms, "testAreSynonyms");
}

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