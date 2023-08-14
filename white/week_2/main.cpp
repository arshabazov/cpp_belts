#include <iostream>
#include <vector>

int getAverage(const std::vector<int>& v) {
	int average = 0;
	
	for (int i = 0; i < v.size(); ++i) {
		average += v[i];
	}
	average /= v.size();
	
	return average;
}

void getAboveAverageTemp(const std::vector<int>& v) {
	std::vector<int> indecies;
	indecies.reserve(v.size()/2);
	int average = getAverage(v);
	int count = 0;
	
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] > average) {
			++count;
			indecies.push_back(i);
		}
	}
	std::cout << count << '\n';
	for (int i = 0; i < count; ++i) {
		std::cout << indecies[i] << ' ';
	}
	std::cout << '\n';
}

int main() {
	int n, m;
	std::vector<int> v;
	
	std::cin >> n;
	v.reserve(n);
	
	for (int i = 0; i < n; ++i) {
		std::cin >> m;
		v.push_back(m);
	}
	getAboveAverageTemp(v);
	
	return 0;
}