#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_trait.hpp"

namespace ft
{   
    /*-------------------------------------------------------
        reverse_terator
    ---------------------------------------------------------*/
    template<class Iter>
    class reverse_iterator{

    public:

        typedef Iter                                                    iterator_type;
        typedef typename ft::iterator_trait<Iter>::iterator_category    iterator_category;
        typedef typename ft::iterator_trait<Iter>::value_type           value_type;
        typedef typename ft::iterator_trait<Iter>::difference_type      difference_type;
        typedef typename ft::iterator_trait<Iter>::pointer              pointer;
        typedef typename ft::iterator_trait<Iter>::reference            reference;

        reverse_iterator() {Iter();};
        explicit reverse_iterator(iterator_type x) {Iter(x);}
        template<class U>
        reverse_iterator(const reverse_iterator<U> &other) {Iter(other);}
        reverse_iterator &operator=(const vector_iterator &src){_ptr = src._ptr;return(*this);}
        ~reverse_iterator() {};

    private:

    };


}


#endif