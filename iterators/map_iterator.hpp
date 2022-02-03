#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>

namespace ft
{
    /*-------------------------------------------------------
        map_iterator (bidirectional_iterator)
    ---------------------------------------------------------*/
    template <class Tree>
    class map_iterator{
        public:
            typedef typename    std::bidirectional_iterator_tag     iterator_category;
            typedef typename    Tree::node                          value_type;
            typedef typename    std::ptrdiff_t                      difference_type;
            typedef             value_type                          *pointer;
            typedef             value_type                          &reference;
            typedef typename    Tree::value_type                    *content;

            map_iterator(): _ptr(NULL){}
            map_iterator(pointer p): _ptr(p){}
            map_iterator(const map_iterator &src){*this = src;}
            map_iterator &operator=(const map_iterator &src){_ptr = src._ptr;return(*this);}
            ~map_iterator(){}


            //overloads
            content         operator->()const {return (&_ptr->content);}
            reference       operator*()const {return (_ptr->content);}

        
            map_iterator    &operator++(){
                ++_ptr; 
                return (*this);
            }//prefix
		    map_iterator    operator++(int){map_iterator res; res._ptr = _ptr++; return(res);}
		    map_iterator    &operator--(){--_ptr; return (*this);}//prefix
		    map_iterator	operator--(int){map_iterator res; res._ptr = _ptr--; return(res);}

        private:
            pointer _ptr;
    };
};

#endif