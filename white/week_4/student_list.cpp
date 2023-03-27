#include <iostream>
#include <vector>

struct Student {
	std::string name;
	std::string lastname;
	int day;
	int month;
	int year;
};

int main() {
	std::vector<Student> studentList;
	int n;
	std::string name, lastname;
	int d, m, y;
	
	std::cin >> n;
	studentList.reserve(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> name >> lastname;
		std::cin >> d >> m >> y;
		studentList.push_back({name, lastname, d, m, y});
	}
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::string request;
		int index;
		
		std::cin >> request;
		std::cin >> index;
		--index;
		if (request == "name" && (index >= 0) && (index >= 0 && index < studentList.size())) {
			std::cout << studentList[index].name << ' ' 
			<< studentList[index].lastname << std::endl;
		} else if (request == "date" && (index >= 0 && index < studentList.size())) {
			std::cout << studentList[index].day << '.' << studentList[index].month
			<< '.' << studentList[index].year << std::endl;
		} else {
			std::cout << "bad request" << std::endl;
		}
	}
	return 0;
}