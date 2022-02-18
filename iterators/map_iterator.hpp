#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "../containers/map/utility/StructRBT.hpp"

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
            typedef Tree                                            RBT;
            typedef typename    std::ptrdiff_t                      difference_type;
            typedef             value_type                          *pointer;
            typedef             value_type                          &reference;
            typedef typename    Tree::value_type                    *content;

            map_iterator(): _ptr(NULL), _rbt(){}
            map_iterator(pointer p, RBT *r): _ptr(p){_rbt = r;}
            map_iterator(const map_iterator &src){*this = src;}
            map_iterator &operator=(const map_iterator &src){_ptr = src._ptr;_rbt = src._rbt;return(*this);}
            ~map_iterator(){}

            pointer	base(void) const{
			    return (_ptr);
		    }

            //overloads
            content         operator->()const {return (_ptr->content);}
            reference       operator*()const {return (*_ptr->content);}

            //prefix
            map_iterator    &operator++(){
                if (_ptr == _rbt->find_max(_rbt->root) && _ptr->right == _rbt->leafs){
                    _ptr = _rbt->leafs;
                    return (*this);
                }
                if(_ptr->right != _rbt->leafs)
                    _ptr = _rbt->find_min(_ptr->right);
                else{
	    			pointer	parent = _ptr->parent;
	    			pointer	current = _ptr;
    				while ((parent != NULL) && (current == parent->right)){
    					current = parent;
    					parent = current->parent;
    				}
                    _ptr = parent;
    				return (*this);
    			}
                return (*this);
            }
		    map_iterator    operator++(int){map_iterator tmp = *this; ++*this; return tmp;}
            //prefix
		    map_iterator    &operator--(){
                if (_ptr == _rbt->last)
                    _ptr = _ptr->parent;
                else if (_ptr->left != _rbt->leafs)
                    _ptr = _rbt->find_max(_ptr->left);
                else if (_ptr != _rbt->root){
                    pointer current = _ptr->parent;
                    while (current && (_rbt->cmp(_ptr->content->first, current->content->first)))
                        current = current->parent;
                    if (current != _rbt->leafs)
                        _ptr = current;
                }
                return (*this);
            }
		    map_iterator	operator--(int){map_iterator res; res._ptr = _ptr--; return(res);}

            operator map_iterator<const Tree>() const {
			    return (map_iterator<const Tree>(_ptr, _rbt));
		    }

            friend bool		operator== (const map_iterator& lhs, const map_iterator& rhs) {
				return lhs._ptr == rhs._ptr; }
			friend bool 	operator!= (const map_iterator& lhs, const map_iterator& rhs) {
				return lhs._ptr != rhs._ptr; }
        private:
            pointer _ptr;
            RBT     *_rbt;
    };
};

#endif