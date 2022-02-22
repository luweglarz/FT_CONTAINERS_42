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
        reverse_iterator(const reverse_iterator<U> &other) {_underlyingit = other.base();}
        reverse_iterator &operator=(const reverse_iterator &src){_underlyingit = src.base(); return (*this);}
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
        reference   operator*() const {iterator_type ret = base(); --ret; return (*ret);}
        reference   operator[](difference_type n) const {return (_underlyingit[-n-1]);}
        pointer     operator->() const {return(&(operator*()));}

        /*-------------------------------------------------------
        Binary operator overloads
        increments and decrements operators on _underliyngit
        ---------------------------------------------------------*/
        reverse_iterator    &operator++(){_underlyingit.operator--();return (*this);}//prefix
		reverse_iterator    operator++(int){reverse_iterator res = *this; _underlyingit.operator--(); return (res);}
		reverse_iterator    &operator--(){_underlyingit.operator++(); return (*this);}//prefix
		reverse_iterator	operator--(int){reverse_iterator res = *this; _underlyingit.operator++(); return (res);}

        /*-------------------------------------------------------
        Arithmetic operator overloads
        perform arithmetic operations on _underlyingit
        ---------------------------------------------------------*/
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

    /*-------------------------------------------------------
        Non-member operators overloads
    ---------------------------------------------------------*/
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
