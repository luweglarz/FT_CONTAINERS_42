#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"
namespace ft
{
    template <class Iter>
    class map_reverse_iterator{
    public:
        typedef Iter                                                        iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category       iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type              value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type         difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer                 pointer;
        typedef typename ft::iterator_traits<Iter>::reference               reference;
        typedef typename Iter::content_value_type                           *contentptr;
        typedef typename Iter::content_value_type                           &contentref;
        typedef typename Iter::RBT                                          RBT;

        map_reverse_iterator(): _underlyingit() {}
        explicit map_reverse_iterator(iterator_type x):_underlyingit(x){}
        template<class U>
        map_reverse_iterator(const map_reverse_iterator<U> &other) {_underlyingit = other.base();}
        map_reverse_iterator &operator=(const map_reverse_iterator &src){_underlyingit = src.base(); return (*this);}
        ~map_reverse_iterator() {};

        /*-------------------------------------------------------
        Access operator overloads
        base: getter for _underlyingit
        ---------------------------------------------------------*/
        iterator_type base() const {return (_underlyingit);}

        contentptr operator->() const {return(&(operator*()));}
        contentref  operator*() const {iterator_type ret = base(); --ret; return (*ret);}

        map_reverse_iterator    &operator++(){_underlyingit.operator--();return (*this);}//prefix
		map_reverse_iterator    operator++(int){map_reverse_iterator res = *this; _underlyingit.operator--(); return (res);}
		map_reverse_iterator    &operator--(){_underlyingit.operator++(); return (*this);}//prefix
		map_reverse_iterator	operator--(int){map_reverse_iterator res = *this; _underlyingit.operator++(); return (res);}

    protected:
        iterator_type _underlyingit;
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const ft::map_reverse_iterator<Iterator1> &lhs,
                    const ft::map_reverse_iterator<Iterator2> &rhs){return (lhs.base() == rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::map_reverse_iterator<Iterator1> &lhs,
                    const ft::map_reverse_iterator<Iterator2> &rhs){return (lhs.base() != rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator>(const ft::map_reverse_iterator<Iterator1> &lhs,
                    const ft::map_reverse_iterator<Iterator2> &rhs){return (lhs.base() > rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::map_reverse_iterator<Iterator1> &lhs,
                    const ft::map_reverse_iterator<Iterator2> &rhs){return (lhs.base() >= rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator<(const ft::map_reverse_iterator<Iterator1> &lhs,
                    const ft::map_reverse_iterator<Iterator2> &rhs){return (lhs.base() < rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::map_reverse_iterator<Iterator1> &lhs,
                    const ft::map_reverse_iterator<Iterator2> &rhs){return (lhs.base() <= rhs.base());}
};

#endif