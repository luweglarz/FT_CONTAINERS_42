#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "vector_iterator.hpp"
namespace ft
{   
    /*-------------------------------------------------------
        reverse_iterator
    ---------------------------------------------------------*/
    template<class Iter>
    class reverse_iterator{
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

        /*-------------------------------------------------------
        Constructors
        reverse_iterator(): default constructor
        explicit reverse_iterator(iterator_type x): underlying iterator initialized with x
        reverse_iterator(const reverse_iterator<U> &other): underlying iterator initialized with other
        ---------------------------------------------------------*/
        reverse_iterator(): _underlyingit() {}
        explicit reverse_iterator(iterator_type x):_underlyingit(x){}
        template<class U>
        reverse_iterator(const reverse_iterator<U> &other) {_underlyingit(other.base());}
        reverse_iterator &operator=(const reverse_iterator &src){_underlyingit = src.base();return(*this);}
        ~reverse_iterator() {};

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
        reference   operator*() const {iterator_type current = _underlyingit; return(*--current);}
        reference   operator[](difference_type n) const {iterator_type current = _underlyingit; return(*(current + n));}
        pointer     operator->() const {iterator_type current = _underlyingit; return(&(*--current));}

        /*-------------------------------------------------------
        Binary operator overloads
        increments and decrements operators on _underliyngit
        ---------------------------------------------------------*/
        reverse_iterator    &operator++(){++_underlyingit; return (*this);}//prefix
		reverse_iterator    operator++(int){reverse_iterator res; res._underlyingit = _underlyingit--; return(res);}
		reverse_iterator    &operator--(){--_underlyingit; return (*this);}//prefix
		reverse_iterator	operator--(int){reverse_iterator res; res._underlyingit = _underlyingit++; return(res);}

    private:
        iterator_type _underlyingit;
    };

    /*-------------------------------------------------------
        Non-member operators overloads
    ---------------------------------------------------------*/
    template <class Iterator1, class Iterator2>
    bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() == rhs.base);}
    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() != rhs.base);}
    template <class Iterator1, class Iterator2>
    bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() > rhs.base);}
    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() >= rhs.base);}
    template <class Iterator1, class Iterator2>
    bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() < rhs.base);}
    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() <= rhs.base);}
    template <class Iter>
    reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
                                    const reverse_iterator<Iter> &it){reverse_iterator<Iter> res = (it.base() + n); return (res);}
    template <class Iter>
    reverse_iterator<Iter> operator-(typename reverse_iterator<Iter>::difference_type n,
                                    const reverse_iterator<Iter> &it){reverse_iterator<Iter> res = (it.base() - n); return (res);}
};


#endif