#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream input("input.txt");
	std::string line;
	double n = 0;
	std::cout.precision(3);
	std::cout << std::fixed;
	if (input) {
		while (std::getline(input , line)) {
			n = static_cast<double>(std::stod(line));
			std::cout << n << std::endl;
		}
	}
	return 0;
}