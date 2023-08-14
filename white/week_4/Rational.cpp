#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <stdexcept>

int GreatestCommonDivisor(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return GreatestCommonDivisor(b, a % b);
  }
}

class Rational {
private:
	int numerator;
	int denominator;
	
public:
	Rational() : numerator(0), denominator(1) {}
	
	Rational(int new_numerator, int new_denominator) {
		const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
		numerator = new_numerator / gcd;
		denominator = new_denominator / gcd;
		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		} else if (denominator == 0) {
			throw std::invalid_argument("Invalid argument");
		}
	}
	
	int Numerator() const {
		return numerator;
	}
	
	int Denominator() const {
		return denominator;
	}
};

bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs.Numerator() == rhs.Numerator() &&
	lhs.Denominator() == rhs.Denominator();
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return lhs.Numerator() < rhs.Numerator();
	} else {
		return (lhs.Numerator() * rhs.Denominator()) < (rhs.Numerator() * lhs.Denominator());
	}
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator()*rhs.Denominator() +
		rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator()*rhs.Denominator() -
		rhs.Numerator() * lhs.Denominator(),
		lhs.Denominator() * rhs.Denominator());
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(),
		lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw std::domain_error("Division by zero");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(),
		lhs.Denominator() * rhs.Numerator());
}

std::istream& operator>>(std::istream& stream, Rational& rationl) {
	int n, d;
	char c;
	if (stream) {
		stream >> n >> c >> d;
		if (stream) {
			if (c == '/') {
				rationl = Rational(n, d);
			} else {
				stream.setstate(std::ios_base::failbit);
			}
		}
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Rational& rational) {
	stream << rational.Numerator() << '/' << rational.Denominator();
	return stream;
}

void parseInput(std::istream& input) {
	try {	
		Rational frac1, frac2;
		char sign;
		
		input >> frac1 >> sign >> frac2;
		if (sign == '+') {
			std::cout << frac1 + frac2;
		} else if (sign == '-') {
			std::cout << frac1 - frac2;
		} else if (sign == '*') {
			std::cout << frac1 * frac2;
		} else if (sign == '/') {
			std::cout << frac1 / frac2;
		}
	} catch (const std::exception& e) {
		std::cout << e.what();
	}
}

int main() {
	parseInput(std::cin);
	
    return 0;
}