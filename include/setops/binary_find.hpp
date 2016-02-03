#ifndef SETOPS_BINARY_FIND_HPP
#define SETOPS_BINARY_FIND_HPP 

#include <algorithm>

namespace setops {
	template<class Iter, class T>
	inline Iter binary_find(Iter begin, Iter end, T val) {
		Iter i = std::lower_bound(begin, end, val);
		if(i != end && !(val < *i)) return i;
		else return end;
	}
}

#endif
