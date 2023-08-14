#include <iostream>
#include <string>
#include <deque>

int main() {
	int x, n;
	std::cin >> x >> n;
	std::deque<std::string> expression;
	expression.push_back(std::to_string(x));

	for (int i = 0; i < n; ++i) {
		char operation;
		int num;
		std::cin >> operation >> num;
		expression.push_front("(");
		expression.push_back(") ");
		expression.push_back(std::string(1, operation));
		expression.push_back(" ");
		expression.push_back(std::to_string(num));
	}
	for (auto part : expression) {
		std::cout << part;
	}
	std::cout << std::endl;

	return 0;
}
