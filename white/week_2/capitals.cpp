#include <iostream>
#include <map>

int main() {
	std::map<std::string, std::string> handbook;
	std::string command;
	int n;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> command;
		if (command == "CHANGE_CAPITAL") {
			std::string country, capital;
			std::cin >> country >> capital;
			if (handbook.count(country) == 0) {
				handbook[country] = capital;
				std::cout << "Introduce new country " << country
				<< " with capital " << capital << std::endl;
			} else {
				if (handbook[country] == capital) {
					std::cout << "Country " << country << " hasn't changed its capital\n";
				} else {
					std::cout << "Country " << country << " has changed its capital from "
					<< handbook[country] << " to " << capital << std::endl;
					handbook[country] = capital;
				}
			}
		} else if (command == "RENAME") {
			std::string old_country, new_country;
			std::cin >> old_country >> new_country;
			
			if (old_country == new_country || handbook.count(old_country) == 0
				|| handbook.count(new_country) != 0) {
				std::cout << "Incorrect rename, skip\n";
			} else {
				std::string capital = handbook[old_country];
				handbook.erase(old_country);
				handbook[new_country] = capital;
				std::cout << "Country " << old_country << " with capital " << capital
				<< " has been renamed to " << new_country << std::endl;
			}
			
		} else if (command == "ABOUT") {
			std::string country;
			std::cin >> country;
			if (handbook.count(country) == 0) {
				std::cout << "Country " << country << " doesn't exist\n";
			} else {
				std::cout << "Country " << country << " has capital "
				<< handbook[country] << std::endl;
			}
			
		} else if (command == "DUMP") {
			if (handbook.empty()) {
				std::cout << "There are no countries in the world\n";
			} else {
				for (auto& entry : handbook) {
					std::cout << entry.first << '/' << entry.second << ' ';
				}
				std::cout << std::endl;
			}
		} else {
			std::cout << "Unknown Command\n";
		}
	}
	return 0;
}