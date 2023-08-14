#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s) {
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

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint = {}) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw std::runtime_error(os.str());
	}
}

void Assert(bool b, const std::string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const std::string& test_name) {
		try {
			func();
			std::cerr << test_name << " OK" << std::endl;
		} catch (std::exception& e) {
			++fail_count;
			std::cerr << test_name << " fail: " << e.what() << std::endl;
		} catch (...) {
			++fail_count;
			std::cerr << "Unknown exception caught" << std::endl;
		}
	}

  ~TestRunner() {
	if (fail_count > 0) {
		std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
		exit(1);
	}
  }

private:
	int fail_count = 0;
};

bool IsPalindrom(const std::string& str) {
	return std::equal(str.begin(), str.begin() + str.size() / 2, str.rbegin());
}

void testPalindrome() {
	Assert(IsPalindrom(""), "When string is empty");
	Assert(IsPalindrom("a"), "When string is just one character");
	Assert(IsPalindrom(" aba "), "When there spaces at the start and end of the string");
	Assert(IsPalindrom("xxx  xxx"), "When there are spaces in the middle");

	Assert(!IsPalindrom(" aabbaa"), "Spaces must not be ignored");
	Assert(!IsPalindrom("aaabbccbbaa"), " The first symbol is ignored");
	Assert(!IsPalindrom("aabbccbbaaa"), " The last symbol is ignored");
	Assert(!IsPalindrom("abcdba"), "The comparison stops before reaching the middle of the string");
	Assert(!IsPalindrom("Abba"), "Comparison should be case-sensitive");
	Assert(!IsPalindrom("hello"), "Basic check for a word that is not a palindorme");
}

int main() {
	TestRunner runner;
	runner.RunTest(testPalindrome, "testPalindrome");

	return 0;
}
