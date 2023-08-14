#include "phone_number.h"
#include <iostream>
#include <sstream>

PhoneNumber::PhoneNumber(const std::string &international_number) {
	std::istringstream is(international_number);
	char sign = is.get();
	if (sign != '+') {
		throw std::invalid_argument("The \'+\' sign is missing");
	}

	std::getline(is, this->country_code_, '-');
	std::getline(is, this->city_code_, '-');
	std::getline(is, this->local_number_);

	if (this->country_code_.empty() || this->city_code_.empty()
		|| this->local_number_.empty())
	{
		throw std::invalid_argument("Invalid phone number format."
		" Must follow the structure: +XXX-YYY-ZZZZZZ " + international_number);
	}
}

std::string PhoneNumber::GetCountryCode() const {
	return this->country_code_;
}

std::string PhoneNumber::GetCityCode() const {
	return this->city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
	return this->local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
	std::string number = "+" + GetCountryCode() + "-" + GetCityCode()
		+ "-" + GetLocalNumber();

	return number;
}