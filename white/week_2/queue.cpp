#include <iostream>
#include <vector>

#define WORRY "WORRY"
#define QUIET "QUIET"
#define COME "COME"
#define WORRY_COUNT "WORRY_COUNT"

void printWorryCount(const std::vector<bool>& queue) {
	int worried = 0;
	
	for (int i = 0; i < queue.size(); ++i) {
		if (queue[i] == true) {
			++worried;
		}
	}
	std::cout << worried << '\n';
}

int main() {
	std::vector<bool> queue;
	int n, m;
	std::string command;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> command;
		if (command == COME) {
			std::cin >> m;
			queue.resize(queue.size() + m, false);
		} else if (command == WORRY) {
			std::cin >> m;
			queue[m] = true;
		} else if (command == QUIET) {
			std::cin >> m;
			queue[m] = false;
		} else if (command == WORRY_COUNT) {
			printWorryCount(queue);
		} else {
			std::cout << "Unknown Command\n";
		}
	}
	return 0;
}