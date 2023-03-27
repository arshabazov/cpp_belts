#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>

// Реализуйте функции и методы классов и при необходимости добавьте свои
#define ADD "Add"
#define DEL "Del"
#define FIND "Find"
#define PRINT "Print"

class Date {
private:
	int year;
	int month;
	int day;

public:
	Date(int year, int month, int day) : year(year), month(month), day(day) {}

	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}
};

bool operator < (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		} else {
			return lhs.GetMonth() < rhs.GetMonth();
		}
	} else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

bool operator == (const Date& lhs, const Date& rhs) {
	return (lhs.GetYear() == rhs.GetYear()) &&
		(lhs.GetMonth() == rhs.GetMonth()) &&
		(lhs.GetDay() == rhs.GetDay());
}

class Database {
private:
	std::map<Date, std::vector<std::string> > eventList;

public:
	void AddEvent(const Date& date, const std::string& event) {
		if (eventList.count(date) != 0) {
			std::vector<std::string>& events = eventList.at(date);
			std::vector<std::string>::iterator it = std::find(events.begin(),
				events.end(), event);
			if (it != events.end()) {
				eventList[date].push_back(event);
			}
		} else {
			eventList[date].push_back(event);
		}
	}

	bool DeleteEvent(const Date& date, const std::string& event);
	int  DeleteDate(const Date& date);

	void /* ??? */ Find(const Date& date) const;

	void Print() const;
};

// bool parseDateStr(const std::string& dateStr) {
// 	bool correct = true;
// 	int i = 0;
// 	while (correct && i < dateStr.size()) {
// 		if (isdigit(dateStr[i])) {
// 			if (i + 1 < dateStr.size() && dateStr[i + 1] != '-') {
// 				correct = false;
// 			}
// 		} else if (dateStr[i] == '+') {
// 			if (i + 1 < dateStr.size() && !isdigit(dateStr[i + 1])) {
// 				correct = false;
// 			}
// 		} else if (dateStr[i] == '-') {
// 			if (i == 0 && !isdigit(dateStr[i + 1])) {
// 				correct = false;
// 			} else if (i + 1 < dateStr.size()) {
// 				if (!isdigit(dateStr[i + 1]) &&
// 					(dateStr[i + 1] == '-' && dateStr[i + 1] == '+')) {
// 					if (i + 2 < dateStr.size()) {
// 						if (!isdigit(dateStr[i + 2])) {
// 							correct = false;
// 						}
// 					} else {
// 						correct = false;
// 					}
// 				}
// 			} else {
// 				correct = false;
// 			}
// 		}
// 		++i;
// 	}
// 	return correct;
// }

// bool validateDate(int year, int month, int day) {
// 	if (month > 12 || month < 1) {
// 		throw std::logic_error("Month value is invalid: " + std::to_string(year));
// 	} else if (day > 31 || day < 1) {
// 		throw std::logic_error("Month value is invalid: " + std::to_string(year));
// 	}

// 	return true;
// }

Date parseDate(const std::string& date) {
	std::stringstream date_stream(date);

	int year;
	date_stream >> year;

	if (date_stream.peek() != '-') {
		std::cout << "year\n";
		throw std::logic_error("Wrong date format: " + date);
	}
	date_stream.ignore();

	int month;
	date_stream >> month;

	if (date_stream.peek() != '-') {
		std::cout << "month\n";
		throw std::logic_error("Wrong date format: " + date);
	}
	date_stream.ignore();

	int day;
	date_stream >> day;

	if (!date_stream.eof()) {
		std::cout << "day\n";
		throw std::logic_error("Wrong date format: " + date);
	}

	if (month > 12 || month < 1) {
		throw std::logic_error("Month value is invalid: " + std::to_string(year));
	} else if (day > 31 || day < 1) {
		throw std::logic_error("Month value is invalid: " + std::to_string(year));
	}

	return Date(year, month, day);
}

void parseAddCmd(std::stringstream& stream, Database& db) {
	std::string date_str, event;
	stream >> date_str >> event;

	const Date date = parseDate(date_str);
	db.AddEvent(date, event);
}

void parseDelCmd(std::stringstream& stream, Database& db) {
	std::string date_str;
	stream >> date_str;

}

void parseFindCmd(std::stringstream& stream, const Database& db) {

}

void parsePrintCmd(std::stringstream& stream, const Database& db) {

}

void parseInput(const std::string& line, Database& db) {
	std::stringstream stream(line);
	std::string command;
	stream >> command;
	stream.ignore(1);
	if (command == ADD) {
		parseAddCmd(stream, db);
	} else if (command == DEL) {
		parseDelCmd(stream, db);
	} else if (command == FIND) {
		// parseFindCmd(stream, db);
	} else if (command == PRINT) {
		// parsePrintCmd(stream, db);
	} else {
		throw std::logic_error("Unknown command: " + command);
	}
}

int main() {
	Database db;

	std::string line;
	while (std::getline(std::cin, line)) {
		// Считайте команды с потока ввода и обработайте
		if (!line.empty()) {
			parseInput(line, db);
		}
	}

	return 0;
}
