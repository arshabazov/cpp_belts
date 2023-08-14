#include <iostream>
#include <exception>
#include <algorithm>
#include <sstream>
#include <string>
#include <charconv>
#include <numeric>

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

int main() {

	Rational r(4, 6);
	std::cout << r.Numerator() << '/' << r.Denominator()<<'\n';

	r = Rational(1, 2) + Rational(1, 3) - Rational(1, 4);
	if (r == Rational(7, 12)) {
		std::cout << "equal\n";
	}

	r = Rational(1, 2) * Rational(1, 3) / Rational(1, 4);
	if (r == Rational(2, 3)) {
		std::cout << "equal\n";
	}

	{
		std::ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			std::cout << "Rational(-6, 8) should be written as \"-3/4\"" << std::endl;
			return 1;
		}
	}

	{
		std::istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			std::cout << "5/7 is incorrectly read as " << r << std::endl;
			return 2;
		}
	}

	{
		std::istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			std::cout << "Multiple values are read incorrectly: " << r1 << " "
				<< r2 << std::endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			std::cout << "Read from empty stream shouldn't change arguments: "
				<< r1 << " " << r2 << std::endl;
			return 4;
		}
	}

	try {
		Rational r(1, 0);
		std::cout << "Doesn't throw in case of zero denominator" << std::endl;
		return 1;
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << '\n';
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		std::cout << "Doesn't throw in case of division by zero" << std::endl;
		return 2;
	}
	catch (const std::domain_error& e) {
		std::cout << e.what() << '\n';
	}

	std::cout << "OK" << std::endl;
	return 0;
}
