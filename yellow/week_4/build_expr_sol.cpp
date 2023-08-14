
#include <string>
#include <algorithm>
#include <iostream>
#include <deque>
// using namespace std;

int main()
{
	std::deque <std::string> s;
	int num, N;
	std::string sign;	//знак
	std::cin >> num; //число
	std::cin >> N;	//количество действий
	s.push_back(std::to_string(num));
	for (int i = 0; i < N; i++) {
		std::cin >> sign >> num;
		s.push_front("(");
		s.push_back(") ");
		s.push_back(sign);
		s.push_back(" ");
		s.push_back(std::to_string(num));
	}
	for (int i = 0; i < s.size(); i++) {
		std::cout << s[i];
	}	
	return 0;
}

