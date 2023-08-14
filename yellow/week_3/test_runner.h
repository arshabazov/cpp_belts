#pragma once

#include <iostream>
#include <map>
#include <set>
#include <sstream>

// Interface

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s);
template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m);
template <typename T, typename U>
void assertEqual(const T& t, const U& u, const std::string& hint);
void Assert(bool b, const std::string& hint);

class TestRunner {
private:
	int fail_counter = 0;
public:
	template <typename TestFunc>
	void runTest(TestFunc func, const std::string& test_name);
	~TestRunner();
};

// Implementation

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

template <typename T, typename U>
void assertEqual(const T& t, const U& u, const std::string& hint) {
	if (t != u) {
		std::ostringstream os;
		os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
		throw std::runtime_error(os.str());
	}
}

template <typename TestFunc>
void TestRunner::runTest(TestFunc func, const std::string& test_name) {
	try {
		func();
		std::cerr << test_name << " OK" << std::endl;
	} catch (std::runtime_error& e) {
		++fail_counter;
		std::cerr << test_name << " failed: " << e.what() << std::endl;
	}
}