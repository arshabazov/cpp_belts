#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

// using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	std::string bus;
	std::string stop;
	std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q) {
	std::string type;
	is >> type;

	if (type == "NEW_BUS") {
		q.type = QueryType::NewBus;
		int stop_count;
		is >> q.bus >> stop_count;
		q.stops.resize(stop_count);
		for (std::string& stop : q.stops) {
			std::cin >> stop;
		}
	} else if (type == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;	
		is >> q.stop;
	} else if (type == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (type == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	std::vector<std::string> busList;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
	if (r.busList.empty()) {
		return os << "No stop";
	}
	bool first = true;
	for (const std::string& bus: r.busList) {
		if (!first) {
			os << ' ';
		}
		first = false;
		os << bus;
	}
	return os;
}

struct StopsForBusResponse {
	std::string bus;
	std::vector<std::pair<std::string, std::vector<std::string>>> stops_for_busses;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
	if (r.stops_for_busses.empty()) {
		return os << "No bus";
	}
	for (const auto stop_info : r.stops_for_busses) {
		os << "Stop " << stop_info.first << ": ";
		if (stop_info.second.size() == 1) {
			os << "no interchange";
		} else {
			for (const std::string& other_bus : stop_info.second) {
				if (other_bus != r.bus) {
					os << other_bus << ' ';
				}
			}
		}
		os << "\n";
	}
	return os;
}

struct AllBusesResponse {
	std::map<std::string, std::vector<std::string>> response;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
	if (r.response.empty()) {
		return os << "No buses";
	}
	for (const auto& bus_info : r.response) {
		os << "Bus " << bus_info.first << ": ";
		for (const std::string& stop : bus_info.second) {
			os << stop << " ";
		}
		os << "\n";
	}

	return os;
}

class BusManager {
private:
	std::map<std::string, std::vector<std::string>> buses_to_stops, stops_to_buses;

public:
	void AddBus(const std::string& bus, const std::vector<std::string>& stops) {
		buses_to_stops[bus] = stops;

		for (const std::string& stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
 	}
	
	BusesForStopResponse GetBusesForStop(const std::string& stop) const {
		BusesForStopResponse response;

		if (stops_to_buses.count(stop) != 0) {
			response.busList = stops_to_buses.at(stop);
		}
		return response;
	}
	
	StopsForBusResponse GetStopsForBus(const std::string& bus) const {
		std::vector<std::pair<std::string, std::vector<std::string>>> response;

		if (buses_to_stops.count(bus) > 0) {
			for (const auto& stop : buses_to_stops.at(bus)) {
				response.push_back(std::make_pair(stop, stops_to_buses.at(stop)));
			}
		}

		return StopsForBusResponse{bus, response};
	}
	
	AllBusesResponse GetAllBuses() const {
		return AllBusesResponse{buses_to_stops};
	}
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;
	
	std::cin >> query_count;
	
	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		std::cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				std::cout << bm.GetBusesForStop(q.stop) << std::endl;
				break;
			case QueryType::StopsForBus:
				std::cout << bm.GetStopsForBus(q.bus) << std::endl;
				break;
			case QueryType::AllBuses:
				std::cout << bm.GetAllBuses() << std::endl;
				break;
		}
	}
	
	return 0;
}
