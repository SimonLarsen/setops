#ifndef SETOPS_INTERSECTION_HPP
#define SETOPS_INTERSECTION_HPP 

#include <iterator>
#include <utility>

namespace setops {
	template<typename T, typename InputIter1, typename InputIter2>
	class intersection_iterator : public std::iterator<std::input_iterator_tag, T> {
		public:
			intersection_iterator(
				InputIter1 it1,
				InputIter1 it1_end,
				InputIter2 it2,
				InputIter2 it2_end
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

			InputIter1 it1, it1_end;
			InputIter2 it2, it2_end;
	};

	template<typename T, typename InputIter1, typename InputIter2>
	inline std::pair<
		intersection_iterator<T, InputIter1, InputIter2>,
		intersection_iterator<T, InputIter1, InputIter2>
	>
	set_intersection(
		InputIter1 it1,
		InputIter1 it1_end,
		InputIter2 it2,
		InputIter2 it2_end
	) {
		return std::make_pair(
			intersection_iterator<T, InputIter1, InputIter2>(it1, it1_end, it2, it2_end),
			intersection_iterator<T, InputIter1, InputIter2>(it1_end, it1_end, it2_end, it2_end)
		);
	}
}

#endif
