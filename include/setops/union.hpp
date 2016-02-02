#ifndef SETOPS_UNION_HPP
#define SETOPS_UNION_HPP 

#include <iterator>
#include <utility>

namespace setops {
	template<typename T, typename InputIter>
	class union_iterator : public std::iterator<std::input_iterator_tag, T> {
		public:
			union_iterator(
				InputIter it1,
				InputIter it1_end,
				InputIter it2,
				InputIter it2_end
			)
			: it1(it1)
			, it1_end(it1_end)
			, it2(it2)
			, it2_end(it2_end)
			{ }

			bool operator==(const union_iterator &other) {
				return it1 == other.it1 && it2 == other.it2;
			}

			bool operator!=(const union_iterator &other) {
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
			union_iterator &operator++() {
				advance();
				return *this;
			}

			// Postfix
			union_iterator operator++(int) {
				union_iterator out(*this);
				++(*this);
				return out;
			}

		private:
			inline void advance() {
				if(it1 == it1_end) ++it2;
				else if(it2 == it2_end) ++it1;
				else if(*it1 < *it2) ++it1;
				else if(*it2 < *it1) ++it2;
				else { ++it1; ++it2; }
			}

			InputIter it1, it1_end;
			InputIter it2, it2_end;
	};

	template<typename T, typename InputIter>
	inline std::pair<
		union_iterator<T, InputIter>,
		union_iterator<T, InputIter>
	>
	set_union(
		InputIter it1,
		InputIter it1_end,
		InputIter it2,
		InputIter it2_end
	) {
		return std::make_pair(
			union_iterator<T, InputIter>(it1, it1_end, it2, it2_end),
			union_iterator<T, InputIter>(it1_end, it1_end, it2_end, it2_end)
		);
	}
}

#endif
