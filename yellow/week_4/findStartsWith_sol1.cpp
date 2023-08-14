// Created by Alex Vinidiktov on 25.04.2023.

#include <iostream>
#include <vector>
#include <utility>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end,
	char prefix)
{
    auto lower = lower_bound(range_begin, range_end, prefix,
		[](const std::string& a, const char& b) {
			return a[0] < b;
		}
	);
    auto upper = upper_bound(range_begin, range_end, prefix,
		[](const char& a, const std::string& b) {
			return a < b[0];
		}
	);

    return {lower, upper};
}