#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::vector<std::string> findNamesHistory(const std::map<int, std::string>& names, int year)  {
	std::vector<std::string> nameHistory;
	
	for (auto& item : names) {
		if (item.first <= year && (nameHistory.empty() || nameHistory.back() != item.second)) {
			nameHistory.push_back(item.second);
		}
	}

	return nameHistory;
}

std::string buildJoinedName(std::vector<std::string> names) {
	if (names.empty()) {
		return "";
	}
	
	std::reverse(begin(names), end(names));
	std::string joined_name = names[0];
	
	for (int i = 1; i < names.size(); ++i) {
		if (i == 1) {
			joined_name += " (";
		} else {
			joined_name += ", ";
		}
		joined_name += names[i];
	}
	if (names.size() > 1) {
		joined_name += ")";
	}
	
	return joined_name;
}

std::string buildFullName(const std::string& firstName, const std::string& lastName) {
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
		const std::vector<std::string> first_names_history = findFirstNamesHistory(year);
		const std::vector<std::string> last_names_history = findLastNamesHistory(year);
		
		std::string first_name;
		std::string last_name;
		if (!first_names_history.empty()) {
			first_name = first_names_history.back();
		}
		if (!last_names_history.empty()) {
			last_name = last_names_history.back();
		}
		return buildFullName(first_name, last_name);
		// return nullptr;
	}
	
	std::string GetFullNameWithHistory(int year) {
		const std::string firstName = buildJoinedName(findFirstNamesHistory(year));
		const std::string lastName = buildJoinedName(findLastNamesHistory(year));
		
		return buildFullName(firstName,lastName);
	}

private:
	// приватные поля
	std::map<int, std::string> first_names;
	std::map<int, std::string> last_names;
	
	std::vector<std::string> findFirstNamesHistory(int year) {
		return findNamesHistory(first_names, year);
  }
  std::vector<std::string> findLastNamesHistory(int year) {
    return findNamesHistory(last_names, year);
  }
};