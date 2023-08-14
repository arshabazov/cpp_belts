#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <charconv>
#include <numeric>

// using namespace std;

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

class Rational {
public:
	Rational() {  
		numerator = 0;
		denominator = 1;
	}
	Rational(int new_numerator, int new_denominator) {
		if (new_denominator == 0) {
			throw std::invalid_argument("Division by zero");
		}
		const int gcd = std::gcd(new_numerator, new_denominator);
		numerator = new_numerator / gcd;
		denominator = new_denominator / gcd;
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

private:
	int numerator;
	int denominator;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
	return lhs.Numerator() == rhs.Numerator() &&
		lhs.Denominator() == rhs.Denominator();
}

bool operator != (const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
	return {
		lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
	return {
		lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
	return {
		lhs.Numerator() * rhs.Numerator(),
		lhs.Denominator() * rhs.Denominator()
	};
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw std::domain_error("Divizion by zero");
	}
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}


std::istream& operator >> (std::istream& is, Rational& r) {
	int n, d;
	char c;
	is >> n >> c >> d;
	if (is && c == '/') {
		r = Rational(n, d);
	}
	return is;
}

std::ostream& operator << (std::ostream& os, const Rational& r) {
	return os << r.Numerator() << '/' << r.Denominator();
}

bool operator < (const Rational& lhs, const Rational& rhs) {
	return (lhs - rhs).Numerator() < 0;
}

void testDefaultRational() {
	Rational rationl;
	AssertEqual(rationl.Numerator(), 0, "Testing default constructor");
	AssertEqual(rationl.Denominator(), 1, "Testing default constructor");
}

void testRationalContraction() {
	{
		Rational rational(4, 10);
		AssertEqual(rational.Numerator(), 2,
			"Testing when rational number should be contracted");
		AssertEqual(rational.Denominator(), 5,
			"Testing when rational number should be contracted");
	}
	{
		Rational rational(6, 8);
		AssertEqual(rational.Numerator(), 3,
			"Testing when rational number should be contracted");
		AssertEqual(rational.Denominator(), 4,
			"Testing when rational number should be contracted");
	}
}

void testNegativeRational() {
	{
		Rational rational(3, -7);
		AssertEqual(rational.Numerator(), -3, "Testing negative rational");
		AssertEqual(rational.Denominator(), 7, "Testing negative rational");
	}
	{
		Rational rational(-2, -3);
		AssertEqual(rational.Numerator(), 2, 
			"Testing when both numerator and denominator are negative");
		AssertEqual(rational.Denominator(), 3,
			"Testing when both numerator and denominator are negative");
	}

}

void testNaughtNumeratorRational() {
	Rational rational(0, 5);
	AssertEqual(rational.Denominator(), 1,
		"Testing when numerator is 0, denominator should be 1");
}

void testRationalSummation() {
	Rational a(1, 3);
	Rational b(2, 5);
	Rational sum;
	sum = a + b;
	Rational expected(11, 15);
	AssertEqual(sum, expected, "Testing the sum of rational numbers");
}

void testRarionalSubstraction() {
	Rational substraction = Rational(5, 7) - Rational(6, 14);
	Rational expected(4, 14);
	AssertEqual(substraction, expected,
		"Testing the substraction of rational numbers");
}

void testRationalMultiplication() {
	Rational multiplication = Rational(3, 8) * Rational(4, 5);
	Rational expected(12, 40);
	AssertEqual(multiplication, expected,
		"Testing multiplication of rational numbers");
}

void testRationalDevision() {
	Rational devision = Rational(3, 6) / Rational(5, 7);
	Rational expected(21, 30);
	AssertEqual(devision, expected, "Testing devision of rational numbers");
}


int main() {
	TestRunner runner;
	// добавьте сюда свои тесты
	runner.RunTest(testDefaultRational, "testDefaultRational");
	runner.RunTest(testRationalContraction, "testRationalContraction");
	runner.RunTest(testNegativeRational, "testNegativeRational");
	runner.RunTest(testNaughtNumeratorRational, "testNaughtNumeratorRational");
	runner.RunTest(testRationalSummation, "testRationalSummation");
	runner.RunTest(testRarionalSubstraction, "testRarionalSubstraction");
	runner.RunTest(testRationalMultiplication, "testRationalMultiplication");
	runner.RunTest(testRationalDevision, "testRationalDevision");

	return 0;
}
