#include <random>
#include <algorithm>
#include <iostream>
#include <vector>

#include <setops/binary_find.hpp>
#include <setops/difference.hpp>
#include <setops/intersection.hpp>
#include <setops/merge.hpp>
#include <setops/symmetric_difference.hpp>
#include <setops/union.hpp>

int main(int argc, const char *argv[]) {
	std::minstd_rand rgen(std::random_device{}());
	std::uniform_int_distribution<int> rdist(1, 4);
	std::uniform_int_distribution<size_t> size_dist(100, 200);

	std::vector<int> v1;
	std::vector<int> v2;

	size_t n1 = size_dist(rgen);
	size_t n2 = size_dist(rgen);

	int val = 0;
	for(size_t i = 0; i < n1; ++i) {
		val += rdist(rgen);
		v1.push_back(val);
	}

	val = 0;
	for(size_t i = 0; i < n2; ++i) {
		val += rdist(rgen);
		v2.push_back(val);
	}

	auto it = setops::set_intersection<int>(v1.begin(), v1.end(), v2.begin(), v2.end());

	std::vector<int> int_tmp(n1+n2);
	auto int_end = std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), int_tmp.begin());

	auto it1 = it.first;
	auto it2 = int_tmp.begin();

	while(it1 != it.second && it2 != int_end) {
		std::cerr << *it1 << "\t" << *it2 << std::endl;
		if(*it1 != *it2) {
			std::cerr << "ERROR!" << std::endl;
			return 1;
		}
		it1++; it2++;
	}

	if(it1 != it.second || it2 != int_end) {
		std::cerr << "Huh?!" << std::endl;
		return 1;
	}

	return 0;
}
