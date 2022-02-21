#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP


namespace ft{
    template<class InputIt1, class InputIt2>
    bool    lexicographical_compare(InputIt1 first1, InputIt1 last1, 
                                    InputIt1 first2, InputIt2 last2){
        while (first1 != last1 && first2 != last2){
            if (*first1 < *first2)
                return (true);
            if (*first2 < *first1)
                return (false);
            first1++;
            first2++;
        }
        return ((first1== last1) && (first2 != last2));
    }

    template<class Iter1, class Iter2, class Compare>
	bool	lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, Compare cmp)
	{
		while (first1 != last1 && first2 != last2){
            if (cmp(*first1 ,*first2))
                return (true);
            if (cmp(*first2, *first1))
                return (false);
            first1++;
            first2++;
        }
		return ((first1 == last1) && (first2 != last2));
	}
}
#endif