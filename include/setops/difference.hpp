#ifndef SETOPS_DIFFERENCE_HPP
#define SETOPS_DIFFERENCE_HPP 

#include <iterator>
#include <utility>

namespace setops {
	template<typename T, typename InputIter1, typename InputIter2>
	class difference_iterator : public std::iterator<std::input_iterator_tag, T> {
		public:
			difference_iterator(
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

			bool operator==(const difference_iterator &other) {
				return it1 == other.it1;
			}

			bool operator!=(const difference_iterator &other) {
				return it1 != other.it1;
			}

			const T operator*() { return *it1; }
			const T *operator->() { return &(*this); }

			// Prefix
			difference_iterator &operator++() {
				advance();
				return *this;
			}

			// Postfix
			difference_iterator operator++(int) {
				difference_iterator out(*this);
				++(*this);
				return out;
			}

		private:
			inline void advance() {
				it1++;
				search();
			}

			inline void search() {
				for(; it1 != it1_end; ++it1) {
					while(it2 != it2_end && *it2 < *it1) ++it2;
					if(it2 == it2_end || *it2 > *it1) break;
				}
			}

			InputIter1 it1, it1_end;
			InputIter2 it2, it2_end;
	};

	template<typename T, typename InputIter1, typename InputIter2>
	inline std::pair<
		difference_iterator<T, InputIter1, InputIter2>,
		difference_iterator<T, InputIter1, InputIter2>
	>
	set_difference(
		InputIter1 list_begin,
		InputIter1 list_end,
		InputIter2 exclude_begin,
		InputIter2 exclude_end
	) {
		return std::make_pair(
			difference_iterator<T, InputIter1, InputIter2>(list_begin, list_end, exclude_begin, exclude_end),
			difference_iterator<T, InputIter1, InputIter2>(list_end, list_end, exclude_end, exclude_end)
		);
	}
}

#endif
