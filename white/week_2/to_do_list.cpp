#include <vector>
#include <iostream>

void dump(const std::vector<std::string>& day) {
	std::cout << day.size() << ' ';
	for (int i = 0; i < day.size(); ++i) {
		std::cout << day[i] << ' ';
	}
	std::cout << '\n';
}

int main() {
	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int month = 0;
	std::vector<std::vector<std::string> > toDoList(31);
	std::string command, listItem;
	int n, index;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> command;
		if (command == "ADD") {
			std::cin >> index >> listItem;
			toDoList[index - 1].push_back(listItem);
		} else if (command == "NEXT") {
			month = (month + 1) % 12;
			int size = months[month];
			if (toDoList.size() > size) {
				int dif = toDoList.size() - size;	
				std::vector<std::string>& lastDay = toDoList[size - 1];
				
				for (int i = 1; i <= dif; ++i) {
					std::vector<std::string>& temp = toDoList[(size - 1) + i];
					lastDay.insert(end(lastDay), begin(temp), end(temp));
				}
			}
			toDoList.resize(size);
		} else if (command == "DUMP") {
			std::cin >> index;
			dump(toDoList[index - 1]);
		} else {
			std::cout << "Command unknown\n";
		}
	}
	return 0;
}