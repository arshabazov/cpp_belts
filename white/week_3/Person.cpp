#include <iostream>
#include <map>

std::string getName(const std::map<int, std::string>& names, int year)  {
	std::string name;
	
	for (auto& item : names) {
		if (item.first <= year) {
			name = item.second;
		} else {
			break;
		}
	}
	return name;
}

class Person {
public:
	void ChangeFirstName(int year, const std::string& first_name) {
		// добавить факт изменения имени на first_name в год year
		first_names[year] = first_name;
	}
	
	void ChangeLastName(int year, const std::string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
		last_names[year] = last_name;
	}
	
	std::string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		std::string firstName = getName(first_names, year);
		std::string lastName = getName(last_names, year);
		std::string fullName;
		
		if (firstName.empty() && lastName.empty()) {
			fullName = "Incognito";
		} else if (firstName.empty()) {
			fullName = lastName + " with unknown first name";
		} else if (lastName.empty()) {
			fullName = firstName + " with unknown last name";
		} else {
			fullName = firstName + " " + lastName;
		}
		
		return fullName;
	}
	
	std::string GetFullNameWithHistory(int year) {
		// получить все имена и фамилии по состоянию на конец года year
	}

private:
	// приватные поля
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
};

int main() {
	Person person;	
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	std::cout << person.GetFullNameWithHistory(1990) << std::endl;

	person.ChangeFirstName(1966, "Pauline");
	std::cout << person.GetFullNameWithHistory(1966) << std::endl;	
	
	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		std::cout << person.GetFullNameWithHistory(year) << std::endl;
	}	
	
	person.ChangeLastName(1961, "Ivanova");
	std::cout << person.GetFullNameWithHistory(1967) << std::endl;

	return 0;
}