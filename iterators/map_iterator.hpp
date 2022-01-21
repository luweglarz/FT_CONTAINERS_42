#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>

namespace ft
{
    /*-------------------------------------------------------
        map_iterator (bidirectional_iterator)
    ---------------------------------------------------------*/
    template <class T>
    class map_iterator{
        public:
            typedef typename    std::bidirectional_iterator_tag     iterator_category;
            typedef             T                                   value_type;
            typedef typename    std::ptrdiff_t                      difference_type;
            typedef             T                                   *pointer;
            typedef             T                                   &reference;

            map_iterator(): _ptr(NULL){}
            map_iterator(T *p): _ptr(p){}
            map_iterator(const map_iterator &src){*this = src;}
            map_iterator &operator=(const map_iterator &src){_ptr = src._ptr;return(*this);}
            ~map_iterator(){}


            //overloads
            reference   operator*()const {return (*_ptr);}
            pointer     *operator->()const {return (_ptr);}
            T   &operator[](int idx) const {return *(_ptr + idx);}
        
            map_iterator &operator++(){++_ptr; return (*this);}//prefix
		    map_iterator operator++(int){map_iterator res; res._ptr = _ptr++; return(res);}
		    map_iterator	&operator--(){--_ptr; return (*this);}//prefix
		    map_iterator	operator--(int){map_iterator res; res._ptr = _ptr--; return(res);}

        private:
            pointer _ptr;
    };
};

#endif