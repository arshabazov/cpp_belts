#include <iostream>
#include <vector>
#include <map>
#include <utility>

template <typename T1, typename T2>
std::pair<T1, T2> operator * (const std::pair<T1, T2>& p_1, const std::pair<T1, T2>& p_2) {
	T1 t1 = p_1.first * p_2.first;
	T2 t2 = p_1.second * p_2.second;
	return std::make_pair(t1,t2);
}

template <typename T>
T Sqr(T x) {
	return x * x;
}

int main() {
	return 0;
}
