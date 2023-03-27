#include <iostream>
#include <algorithm>

class ReversibleString {
private:
	std::string str;
	
public:
	ReversibleString() {}	
	ReversibleString(const std::string& str) : str(str) {}
	~ReversibleString() {}
	
	void Reverse() {
		std::reverse(begin(str), end(str));
	}
	
	std::string ToString() const {
		return str;
	}
};