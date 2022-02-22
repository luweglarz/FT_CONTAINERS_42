#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "../containers/map/utility/StructRBT.hpp"

namespace ft
{
    template <class Tree, class Pair>
    class map_iterator{
        public:
            typedef             Pair                                content_value_type;
            typedef typename    std::bidirectional_iterator_tag     iterator_category;
            typedef typename    Tree::node                          value_type;
            typedef             Tree                                RBT;
            typedef typename    std::ptrdiff_t                      difference_type;
            typedef             value_type                          *pointer;
            typedef             value_type                          &reference;
            typedef             Pair                                *contentptr;
            typedef             Pair                                &contentref;

            map_iterator(): _ptr(NULL), _rbt(){}
            map_iterator(pointer p, RBT *r): _ptr(p){_rbt = r;}
            map_iterator(const map_iterator &src){*this = src;}
            map_iterator &operator=(const map_iterator &src){_ptr = src._ptr;_rbt = src._rbt;return(*this);}
            ~map_iterator(){}

            pointer	base(void) const{
			    return (_ptr);
		    }

            contentptr      operator->()const {return (_ptr->content);}
            contentref      operator*()const {return (*_ptr->content);}

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
		    map_iterator    operator++(int){map_iterator ret = *this; ++*this; return ret;}

		    map_iterator    &operator--(){
                if (_ptr == _rbt->first){
                    _ptr = _rbt->last;
                    return (*this);
                }
                if (_ptr == _rbt->last){
                    _ptr = _rbt->find_max(_rbt->root);
                    return (*this);
                }
                else if (_ptr->left != _rbt->leafs)
                    _ptr = _rbt->find_max(_ptr->left);
                else if (_ptr->parent != NULL){
                    pointer current = _ptr->parent;
                    while (current != NULL && _ptr == current->left){
                        _ptr = current;
                        current = current->parent;
                    }
                    _ptr = current;
                }
                return (*this);
            }
		    map_iterator	operator--(int){map_iterator ret = *this; --*this; return ret;}

            operator map_iterator<const Tree, const Pair>() const {
			    return (map_iterator<const Tree, const Pair>(_ptr, _rbt));
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