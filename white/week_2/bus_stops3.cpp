#include <iostream>
#include <map>
#include <set>

int main() {
	std::map<std::set<std::string>, int> bus_routes;
	int n;
	int index = 0;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int m;
		std::cin >> m;
		std::set<std::string> stops;
		for (int j = 0; j < m; ++j) {
			std::string input;
			std::cin >> input;
			stops.insert(input);
		}
		if (bus_routes.count(stops) == 0) {
			bus_routes[stops] = ++index;
			std::cout << "New bus " << index << std::endl;
		} else {
			std::cout << "Already exists for " << bus_routes[stops] << std::endl;
		}
	}
	
	return 0;
}