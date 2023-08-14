#include <iostream>
#include <cstdlib>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
	RandomIt range_end, char prefix)
{
    std::string prefix_s {prefix};
	return equal_range(range_begin, range_end, prefix_s,
		[](const std::string& s, const std::string& v) {
			return s[0] < v[0];
		}
	);
}