#ifndef SETOPS_SYMMETRIC_DIFFERENCE_HPP
#define SETOPS_SYMMETRIC_DIFFERENCE_HPP 

#include <iterator>
#include <utility>

namespace setops {
	template<typename T, typename InputIter>
	class symmetric_difference_iterator : public std::iterator<std::input_iterator_tag, T> {
		public:
			symmetric_difference_iterator(
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

			bool operator==(const symmetric_difference_iterator &other) {
				return it1 == other.it1 && it2 == other.it2;
			}

			bool operator!=(const symmetric_difference_iterator &other) {
				return it1 != other.it1 || it2 != other.it2;
			}

			const T operator*() {
				if(it1 == it1_end) return *it2;
				else if(it2 == it2_end) return *it1;
				else if(*it1 < *it2) return *it1;
				else return *it2;
			}

			const T *operator->() { return &(*this); }

			// Prefix
			symmetric_difference_iterator &operator++() {
				advance();
				return *this;
			}

			// Postfix
			symmetric_difference_iterator operator++(int) {
				symmetric_difference_iterator out(*this);
				++(*this);
				return out;
			}

		private:
			inline void advance() {
				if(it1 == it1_end) ++it2;
				else if(it2 == it2_end) ++it1;
				else if(*it1 < *it2) ++it1;
				else ++it2;

				search();
			}

			inline void search() {
				while(it1 != it1_end && it2 != it2_end && *it1 == *it2) {
					++it1;
					++it2;
				}
			}

			InputIter it1, it1_end;
			InputIter it2, it2_end;
	};

	template<typename T, typename InputIter>
	inline std::pair<
		symmetric_difference_iterator<T, InputIter>,
		symmetric_difference_iterator<T, InputIter>
	>
	set_symmetric_difference(
		InputIter it1,
		InputIter it1_end,
		InputIter it2,
		InputIter it2_end
	) {
		return std::make_pair(
			symmetric_difference_iterator<T, InputIter>(it1, it1_end, it2, it2_end),
			symmetric_difference_iterator<T, InputIter>(it1_end, it1_end, it2_end, it2_end)
		);
	}
}

#endif
