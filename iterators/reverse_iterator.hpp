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

        typedef Iter                                                        iterator_type;
        typedef typename ft::iterator_traits<Iter>::iterator_category       iterator_category;
        typedef typename ft::iterator_traits<Iter>::value_type              value_type;
        typedef typename ft::iterator_traits<Iter>::difference_type         difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer                 pointer;
        typedef typename ft::iterator_traits<Iter>::reference               reference;

        // reverse_iterator() {iterator_type();};
        // explicit reverse_iterator(iterator_type x) {iterator_type(x);}
        // template<class U>
        // reverse_iterator(const reverse_iterator<U> &other) {iterator_type(other);}
        // reverse_iterator &operator=(const reverse_iterator &src){_ptr = src._ptr;return(*this);}
        // ~reverse_iterator() {};

    private:

    };


}


#endif