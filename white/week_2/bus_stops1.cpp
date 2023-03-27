#include <iostream>
#include <map>
#include <vector>

int main() {
	std::map<std::string, std::vector<std::string> > bus_routes;
	std::map<std::string, std::vector<std::string> > bus_stops;
	int n;
	
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::string command;
		std::cin >> command;
		if (command == "NEW_BUS") {
			std::string bus;
			int stops;
			std::cin >> bus;
			std::cin >> stops;
			for (int j = 0; j < stops; ++j) {
				std::string stop_name;
				std::cin >> stop_name;
				bus_routes[bus].push_back(stop_name);
				bus_stops[stop_name].push_back(bus);
			}
		} else if (command == "BUSES_FOR_STOP") {
			std::string stop;
			std::cin >> stop;
			if (bus_stops.count(stop) == 0) {
				std::cout << "No stop\n";
			} else {
				std::vector<std::string>& buses = bus_stops[stop];
				for (auto& bus : buses) {
					std::cout << bus << ' ';
				}
				std::cout << std::endl;
			}
		} else if (command == "STOPS_FOR_BUS") {
			std::string the_bus;
			std::cin >> the_bus;
			if (bus_routes.count(the_bus) == 0) {
				std::cout << "No bus\n";
			} else {
				std::vector<std::string>& stops = bus_routes[the_bus];
				for (auto& stop : stops) {
					std::cout << "Stop " << stop << ": ";
					std::vector<std::string>& buses = bus_stops[stop];
					if (buses.size() == 1) {
						std::cout << "no interchange";
					} else {
						for (auto& bus : buses) {
							if (bus != the_bus) {
								std::cout << bus << ' ';
							}
						}
					}
					std::cout <<std::endl;
				}
			}
		} else if (command == "ALL_BUSES") {
			if (bus_routes.size() == 0) {
				std::cout << "No buses\n";
			} else {
				for (auto& bus_info : bus_routes) {
					std::cout << "Bus " << bus_info.first << ": ";
					for (auto& stop : bus_info.second) {
						std::cout << stop << ' ';
					}
					std::cout << std::endl;
				}
			}
		}
	}
	
	return 0;
}