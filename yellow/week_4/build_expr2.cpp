#include <iostream>
#include <string>
#include <deque>
#include <stack>

enum class Priority {
	low = 1,
	high = 2
};

struct Sign {
	Priority priority;
	char sign;
};

std::istream& operator >> (std::istream& is, Sign& sign) {
	char c;
	is >> c;
	if (c == '+' || c == '-') {
		sign.priority = Priority::low;
		sign.sign = c;
	} else {
		sign.priority = Priority::high;
		sign.sign = c;
	}
	return is;
}

int main() {
	int x, n;
	std::cin >> x >> n;
	std::deque<std::string> expression;
	std::stack<Sign> sign_stack;
	expression.push_back(std::to_string(x));

	for (int i = 0; i < n; ++i) {
		Sign operation;
		int num;
		std::cin >> operation >> num;
		if (!sign_stack.empty()) {
			if (sign_stack.top().priority == Priority::low
				&& operation.priority == Priority::high)
			{
				expression.push_front("(");
				expression.push_back(")");
			}
			sign_stack.pop();
		}
		sign_stack.push(operation);
		expression.push_back(" ");
		expression.push_back(std::string(1, operation.sign));
		expression.push_back(" ");
		expression.push_back(std::to_string(num));
	}
	for (auto part : expression) {
		std::cout << part;
	}
	std::cout << std::endl;

	return 0;
}