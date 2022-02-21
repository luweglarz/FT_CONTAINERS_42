#ifndef MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"
namespace ft
{
    /*-------------------------------------------------------
        map_reverse_iterator
    ---------------------------------------------------------*/
    template <class Iter>
    class map_reverse_iterator{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef Iter                                                        iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category       iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type              value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type         difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer                 pointer;
        typedef typename ft::iterator_traits<Iter>::reference               reference;
        typedef typename Iter::content_value_type                           *contentptr;
        typedef typename Iter::content_value_type                           &contentref;
        typedef typename Iter::RBT                                          RBT;
        /*-------------------------------------------------------
        Constructors
        map_reverse_iterator(): default constructor
        explicit map_reverse_iterator(iterator_type x): underlying iterator initialized with x
        map_reverse_iterator(const map_reverse_iterator<U> &other): underlying iterator initialized with other
        ---------------------------------------------------------*/
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
        
        /*-------------------------------------------------------
        Access operator overloads
        *: returns a reference to previous _underlyingit (--_underlyingit)
        []: returns a reference at specified position (n)
        ->: returns a pointer to previous _underlyingit (--_underlyingit)
        ---------------------------------------------------------*/
        contentptr operator->() const {return(_underlyingit.base()->content);}
        contentref  operator*() const {return (*_underlyingit);}

        /*-------------------------------------------------------
        Binary operator overloads
        increments and decrements operators on _underliyngit
        ---------------------------------------------------------*/
        map_reverse_iterator    &operator++(){--_underlyingit;return (*this);}//prefix
		map_reverse_iterator    operator++(int){map_reverse_iterator res(*this); res._underlyingit = _underlyingit--; return(res);}
		map_reverse_iterator    &operator--(){++_underlyingit; return (*this);}//prefix
		map_reverse_iterator	operator--(int){map_reverse_iterator res(*this); res._underlyingit = _underlyingit++; return(res);}

    protected:
        iterator_type _underlyingit;
    };

    /*-------------------------------------------------------
        Non-member operators overloads
    ---------------------------------------------------------*/
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