setops
======

C++ set operations on ranges without copying.

## Example ##

```c++
#include <vector>
#include <iostream>
#include <algorithm>
#include <setops/intersection.hpp>

int main(int argc, const char *argv[]) {
	std::vector<int> v1 = {1, 2, 4, 6, 7, 8};
	std::vector<int> v2 = {2, 3, 5, 6, 8};

	auto it = setops::set_intersection<int>(v1.begin(), v1.end(), v2.begin(), v2.end());

	std::for_each(it.first, it.second, [](int i) { std::cout << i << " "; });
	std::cout << std::endl;

	return 0;
}
```

Output

    2 6 8

## Benchmarks ##
