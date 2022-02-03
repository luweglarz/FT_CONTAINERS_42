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
            content         operator->()const {return (_ptr->content);}
            reference       operator*()const {return (_ptr->content);}

            //prefix
            map_iterator    &operator++(){
                if(_ptr->right != NULL)
                    _ptr = Tree::find_min(_ptr->right);
                else if (_ptr != Tree::root){
                    pointer current = _ptr->parent;
                    while (current && (_ptr->cmp(current->content->first, _ptr->content->first)))
                        current = current->parent;
                    if (current != NULL)
                        _ptr = current;
                }
                return (*this);
            }
		    map_iterator    operator++(int){map_iterator tmp = *this; ++*this; return tmp;}
            //prefix
		    map_iterator    &operator--(){
                if (_ptr == Tree::last)
                    _ptr = _ptr->parent;
                else if (_ptr->left != NULL)
                    _ptr = Tree::find_max(_ptr->left);
                else if (_ptr != Tree::root){
                    pointer current = _ptr->parent;
                    while (current && (_ptr->cmp(_ptr->content->first, current->content->first)))
                        current = current->parent;
                    if (current != NULL)
                        _ptr = current;
                }
                return (*this);
            }
		    map_iterator	operator--(int){map_iterator res; res._ptr = _ptr--; return(res);}

            bool operator==(const map_iterator &rhs) const {
                if (_ptr == rhs._ptr)
                    return (true);
                return (false);
            }
            bool operator!=(const map_iterator &rhs) const {
                if (_ptr != rhs._ptr)
                    return (true);
                return (false);
            }
        private:
            pointer _ptr;
    };
};

#endif