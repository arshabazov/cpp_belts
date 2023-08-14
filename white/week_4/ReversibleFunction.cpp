#include <iostream>
#include <vector>
#include <algorithm>

class FunctionPart {
private:
	char operation;
	double value;
public:
	FunctionPart(char new_operation, double new_val) {
		operation = new_operation;
		value = new_val;
	}
	
	double Apply(double source_val) const {
		if (operation == '+') {
			return source_val + value;
		} else if (operation == '-') {
			return source_val - value;
		} else if (operation == '*') {
			return source_val * value;
		} else {
			return source_val / value;
		}
	}
	
	void Invert() {
		if (operation != '+') {
			operation = '-';
		} else if (operation == '-') {
			operation = '+';
		} else if (operation == '*') {
			operation = '/';
		} else if (operation == '/') {
			operation = '*';
		}
	}
};

class Function {
private:
	std::vector<FunctionPart> parts;
	
public:
	void AddPart(char operation, double value) {
		parts.push_back({operation, value});
	}
	
	double Apply(double value) const {
		for (const FunctionPart& part: parts) {
			value = part.Apply(value);
		}
		return value;
	}
	
	void Invert() {
		for (FunctionPart& part: parts) {
			part.Invert();
		}
		std::reverse(begin(parts), end(parts));
	}
};