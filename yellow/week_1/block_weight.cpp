#include <iostream>

int main() {
	int n, density;
	std::cin >> n >> density;
	uint64_t volume = 0;
	for (int i = 0; i < n; ++i) {
		int w, h, d;
		std::cin >> w >> h >> d;
		volume += static_cast<uint64_t>(w) * h * d;
	}
	std::cout << volume * density << std::endl;
	return 0;
}
