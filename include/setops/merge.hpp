#ifndef SETOPS_MERGE_HPP
#define SETOPS_MERGE_HPP 

#include <iterator>
#include <utility>

namespace setops {
	template<typename T, typename InputIter1, typename InputIter2>
	class merge_iterator : public std::iterator<std::input_iterator_tag, T> {
		public:
			merge_iterator(
				InputIter1 it1,
				InputIter1 it1_end,
				InputIter2 it2,
				InputIter2 it2_end
			)
			: it1(it1)
			, it1_end(it1_end)
			, it2(it2)
			, it2_end(it2_end)
			{ }

			bool operator==(const merge_iterator &other) {
				return it1 == other.it1 && it2 == other.it2;
			}

			bool operator!=(const merge_iterator &other) {
				return it1 != other.it1 || it2 != other.it2;
			}

			const T operator*() {
				if(it1 == it1_end) return *it2;
				else if(it2 == it2_end) return *it1;
				else if(*it1 <= *it2) return *it1;
				else return *it2;
			}

			const T *operator->() { return &(*this); }

			// Prefix
			merge_iterator &operator++() {
				advance();
				return *this;
			}

			// Postfix
			merge_iterator operator++(int) {
				merge_iterator out(*this);
				++(*this);
				return out;
			}

		private:
			inline void advance() {
				if(it1 == it1_end) ++it2;
				else if(it2 == it2_end) ++it1;
				else if(*it1 <= *it2) ++it1;
				else ++it2;
			}

			InputIter1 it1, it1_end;
			InputIter2 it2, it2_end;
	};

	template<typename T, typename InputIter1, typename InputIter2>
	inline std::pair<
		merge_iterator<T, InputIter1, InputIter2>,
		merge_iterator<T, InputIter1, InputIter2>
	>
	merge(
		InputIter1 it1,
		InputIter1 it1_end,
		InputIter2 it2,
		InputIter2 it2_end
	) {
		return std::make_pair(
			merge_iterator<T, InputIter1, InputIter2>(it1, it1_end, it2, it2_end),
			merge_iterator<T, InputIter1, InputIter2>(it1_end, it1_end, it2_end, it2_end)
		);
	}
}

#endif
