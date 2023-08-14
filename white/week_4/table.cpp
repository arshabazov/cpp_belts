#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream input("input.txt");
	std::cout.precision(3);
	int n, m , k;
	std::cout << std::fixed;
	if (input) {
		input >> n;
		input.ignore(1);
		input >> m;
		std::cout << std::setfill(' ');
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				input >> k;
				input.ignore(1);
				std::cout << std::setw(10) << k;
				if (j < m - 1) {
					std::cout << ' ';
				}
			}
			if (i < n - 1) {
				std::cout << std::endl;
			}
		}
	}
	return 0;
}