#ifndef SETOPS_INTERSECTION_HPP
#define SETOPS_INTERSECTION_HPP 

#include <iterator>
#include <utility>

namespace setops {
	template<typename T, typename InputIter>
	class intersection_iterator : public std::iterator<std::input_iterator_tag, T> {
		public:
			intersection_iterator(
				InputIter it1,
				InputIter it1_end,
				InputIter it2,
				InputIter it2_end
			)
			: it1(it1)
			, it1_end(it1_end)
			, it2(it2)
			, it2_end(it2_end)
			{
				search();
			}

			bool operator==(const intersection_iterator &other) {
				return it1 == other.it1 && it2 == other.it2;
			}

			bool operator!=(const intersection_iterator &other) {
				return it1 != other.it1 || it2 != other.it2;
			}

			const T operator*() { return *it1; }

			const T *operator->() { return &(*this); }

			// Prefix
			intersection_iterator &operator++() {
				advance();
				return *this;
			}

			// Postfix
			intersection_iterator operator++(int) {
				intersection_iterator out(*this);
				++(*this);
				return out;
			}

		private:
			inline void advance() {
				++it1;
				++it2;
				search();
			}

			inline void search() {
				while(it1 != it1_end && it2 != it2_end && *it1 != *it2) {
					if(*it1 < *it2) ++it1;
					else if(*it2 < *it1) ++it2;
				}

				if(it1 == it1_end || it2 == it2_end) {
					it1 = it1_end;
					it2 = it2_end;
				}
			}

			InputIter it1, it1_end;
			InputIter it2, it2_end;
	};

	template<typename T, typename InputIter>
	inline std::pair<
		intersection_iterator<T, InputIter>,
		intersection_iterator<T, InputIter>
	>
	set_intersection(
		InputIter it1,
		InputIter it1_end,
		InputIter it2,
		InputIter it2_end
	) {
		return std::make_pair(
			intersection_iterator<T, InputIter>(it1, it1_end, it2, it2_end),
			intersection_iterator<T, InputIter>(it1_end, it1_end, it2_end, it2_end)
		);
	}
}

#endif
