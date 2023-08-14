#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

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

int GetDistinctRealRootCount(double a, double b, double c) {
	double D = std::pow(b, 2) - 4 * a * c;
	
	if (a == 0) {
		if (b != 0) {
			// std::cout << -c / b << std::endl;
			return 1;
		}
	} else if (D == 0) {
		// std::cout << -b / (2 * a) << std::endl;
		return 1;
	} else if (D > 0) {
		// double x1 = (-b + sqrt(D)) / (2 * a);
		// double x2 = (-b - sqrt(D)) / (2 * a);
		// std::cout << x1 << " " << x2 << std::endl;
		return 2;
	}
	
	return 0;
}

void test_no_roots() {
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "testing when a = 0 and b = 0");
}

void test_linear_equation() {
	AssertEqual(GetDistinctRealRootCount(0, 3, 1), 1, "testing when a = 0");
}

void test_positive_discriminant() {
	AssertEqual(GetDistinctRealRootCount(1, 7, -60), 2, "testing when D > 0");
}

void test_zero_discriminant() {
	AssertEqual(GetDistinctRealRootCount(1, -6, 9), 1, "testing when D = 0");
}

void test_negative_discriminant() {
	AssertEqual(GetDistinctRealRootCount(-3, 2, -1), 0, "testing when D < 0");
}


int main() {
	TestRunner runner;
	// добавьте сюда свои тесты
	runner.RunTest(test_no_roots, "test_no_roots");
	runner.RunTest(test_linear_equation, "test_linear_equation");
	runner.RunTest(test_positive_discriminant, "test_positive_discriminant");
	runner.RunTest(test_zero_discriminant, "test_zero_discriminant");
	runner.RunTest(test_negative_discriminant, "test_negative_discriminant");
	
	return 0;
}
