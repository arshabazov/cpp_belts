#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <sstream>
#include <iomanip>

struct Date {
	int year;
	int month;
	int day;

	Date(int y, int m, int d) : year(y), month(m), day(d) {}
};

// typedef std::vector<std::tuple<Date, Date, int>> Income_info;

bool operator < (const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) <
		std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Date& lhs, const Date& rhs) {
	return std::tie(lhs.year, lhs.month, lhs.day) ==
		std::tie(rhs.year, rhs.month, rhs.day);
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
  stream << std::setw(4) << std::setfill('0') << date.year <<
      "-" << std::setw(2) << std::setfill('0') << date.month <<
      "-" << std::setw(2) << std::setfill('0') << date.day;
  return stream;
}

class Income {
private:
	Date start;
	int days;
	double income;

	int computeDays(const Date& start, const Date& end) {
		return 0;
	}

public:
	Income(const Date& date, const Date& period, double amount)
		: start(date), days(computeDays(date, period)), income(amount)
	{}
};

Date parseDate(const std::string& date) {
	std::istringstream date_stream(date);
	bool ok = true;

	int year;
	ok = ok && (date_stream >> year);
	ok = ok && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int month;
	ok = ok && (date_stream >> month);
	ok = ok && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int day;
	ok = ok && (date_stream >> day);
	ok = ok && date_stream.eof();
	
	if (!ok) {
		throw std::logic_error("Wrong date format: " + date);
	}
	
	return Date(year, month, day);
}

/*
void computeIncome(const Income_info& info,
	const Date& date1, const Date& date2)
{
	// for (int i = 0; i < info.size(); ++i) {
	// 	std::cout << std::get<0>(info[i]) << " "
	// 	<< std::get<1>(info[i]) << " "
	// 	<< std::get<2>(info[i]) << std::endl;
	// }

}
*/

int main() {
	int q;
	// Income_info income_info;
	std::vector<Income> income_info;
	std::cin >> q;

	for (int i = 0; i < q; ++i) {
		std::string cmd;
		std::cin >> cmd;

		if (cmd == "ComputeIncome") {
			std::string str1, str2;
			std::cin >> str1 >> str2;
			Date date1 = parseDate(str1);
			Date date2 = parseDate(str2);
			// computeIncome(income_info, date1, date2);
		} else if (cmd == "Earn") {
			std::string str1, str2;
			double amount;
			std::cin >> str1 >> str2 >> amount;
			Date date1 = parseDate(str1);
			Date date2 = parseDate(str2);
			income_info.emplace_back(date1, date2, amount);
		} else {
			std::cout << "Uknown command\n";
		}
	}

	return 0;
}