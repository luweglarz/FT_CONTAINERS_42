#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "vector_iterator.hpp"

namespace ft
{   
    template<class Iter>
    class reverse_iterator{
    public:
        typedef Iter                                                        iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category       iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type              value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type         difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer                 pointer;
        typedef typename ft::iterator_traits<Iter>::reference               reference;

        reverse_iterator(): _underlyingit() {}
        explicit reverse_iterator(iterator_type x):_underlyingit(x){}
        template<class U>
        reverse_iterator(const reverse_iterator<U> &other) {_underlyingit = other.base();}
        reverse_iterator &operator=(const reverse_iterator &src){_underlyingit = src.base(); return (*this);}
        ~reverse_iterator() {};

        iterator_type base() const {return (_underlyingit);}

        reference   operator*() const {iterator_type ret = base(); --ret; return (*ret);}
        reference   operator[](difference_type n) const {return (_underlyingit[-n-1]);}
        pointer     operator->() const {return(&(operator*()));}

        reverse_iterator    &operator++(){_underlyingit.operator--();return (*this);}//prefix
		reverse_iterator    operator++(int){reverse_iterator res = *this; _underlyingit.operator--(); return (res);}
		reverse_iterator    &operator--(){_underlyingit.operator++(); return (*this);}//prefix
		reverse_iterator	operator--(int){reverse_iterator res = *this; _underlyingit.operator++(); return (res);}

        reverse_iterator    operator+(difference_type n) const{return (reverse_iterator(_underlyingit - n));}
        reverse_iterator    operator-(difference_type n) const{return (reverse_iterator(_underlyingit + n));}
        reverse_iterator    &operator+=(difference_type n){_underlyingit.operator-=(n);; return (*this);}
        reverse_iterator    &operator-=(difference_type n){_underlyingit.operator+=(n);; return (*this);}

        difference_type	operator-(const reverse_iterator<Iter> &other){return (other.base() - _underlyingit);}

		difference_type	operator+(const reverse_iterator<Iter> &other){return (other.base() + _underlyingit);}

		operator reverse_iterator<const Iter>() const {
			return (reverse_iterator<const Iter>(base()));
		}

    protected:
        iterator_type _underlyingit;
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){
                        if (lhs.base() == rhs.base())
                            return (true);
                        return (false);}
    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() != rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() < rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() <= rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() > rhs.base());}
    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs){return (lhs.base() >= rhs.base());}
                    
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type 
    operator+(const reverse_iterator<Iterator> &lhs,const reverse_iterator<Iterator> &rhs){
        return (rhs.base() + lhs.base());}
    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &it){return (it + n);}
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type 
    operator-(const reverse_iterator<Iterator> &lhs,const reverse_iterator<Iterator> &rhs){
        return (rhs.base() - lhs.base());}
    template <class Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &it){return (it - n);}
};


#endif
