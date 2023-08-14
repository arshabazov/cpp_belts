#include <iostream>
#include <map>
#include <vector>

int main() {
	std::map<std::vector<std::string>, int> routes;
	int n;
	int index = 0;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int m;
		std::cin >> m;
		std::vector<std::string> stops(m);
		for (auto& stop : stops) {
			std::cin >> stop;
		}
		if (routes.count(stops) == 0) {
			routes[stops] = ++index;
			std::cout << "New bus " << routes[stops] << std::endl;
		} else {
			std::cout << "Already exists for " << routes[stops] << std::endl;
		}
	}
	return 0;
}