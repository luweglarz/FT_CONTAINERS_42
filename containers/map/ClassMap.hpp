#ifndef map_HPP
#define map_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "utility/pair.hpp"
#include "../../iterators/map_iterator.hpp"
#include "../../iterators/map_reverse_iterator.hpp"
#include "utility/StructRBT.hpp"
#include "../../SFINAE/enable_if.hpp"
#include "../../SFINAE/is_integral.hpp"

namespace ft
{

    template < class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef Key                                                 key_type;
        typedef T                                                   mapped_key;
        typedef ft::pair<const key_type, mapped_key>                value_type;
        typedef size_t                                              size_type;
        typedef std::ptrdiff_t                                      difference_type;
        typedef Compare                                             key_compare;

        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
    private:
        typedef RBT<value_type, key_compare>                        Tree;
        typedef typename Tree::node                                 node;
        typedef typename Tree::pointer                              ptrnode;
        typedef typename Tree::allocator_type                       Nalloc;
    public:
        typedef ft::map_iterator<Tree>                              iterator;
        typedef ft::map_iterator<const Tree>                        const_iterator;
        typedef ft::map_reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::map_reverse_iterator<const_iterator>                const_reverse_iterator;

        //Constructors
        /*-------------------------------------------------------
        Default constructor that creates an empty map
        comp: comparator object
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit map(const Compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _mallocator(alloc), _size(0), _cmp(comp), 
                    _RBT(), _nallocator(){
        }

        /*-------------------------------------------------------
        fill constructor that creates a map with a range of iterators
        first: iterator that points on the first element of the range
        last: iterator that points on the last element of the range
        comp: comparator object
        alloc: the allocator object
        ---------------------------------------------------------*/
        template <class InputIterator>
        explicit map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
                    _mallocator(alloc), _cmp(comp), _RBT(){
            while (first != last){
                _size += insert(first->first);
                first++;
            }
        }

        /*-------------------------------------------------------
        copy constructor that creates a map with a range of iterators
        x: source map object to copy
        ---------------------------------------------------------*/
        map(const map &x){
            *this = x;
        }

        map &operator=(const map &x){
            _mallocator = x._mallocator;
            _size = x._size;
            _cmp = x._cmp;
            _RBT = x._RBT;
        }

        ~map(){
            erase(begin(), end());
        }
    
        //Iterators
        /*-------------------------------------------------------
        begin function that returns an iterator/const_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        iterator begin(){
            return (iterator(_RBT.first, &_RBT));
        }
        
        const_iterator begin() const{
            return (const_iterator(_RBT.first, &_RBT));
        }

        /*-------------------------------------------------------
        end function that returns an iterator/const_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        iterator end(){
            return (iterator(_RBT.last, &_RBT));
        }

        const_iterator end() const{
            return (const_iterator(_RBT.last, &_RBT));
        }

        /*-------------------------------------------------------
        rbegin function that returns a reverse_iterator/const_reverse_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        reverse_iterator rbegin(){
            return (reverse_iterator(_RBT.last, &_RBT));
        }

        const_reverse_iterator rbegin() const{
            return (const_reverse_iterator(_RBT.last, &_RBT));
        }

        /*-------------------------------------------------------
        rend function that returns a reverse_iterator/const_reverse_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        reverse_iterator rend(){
            return (reverse_iterator(_RBT.first, &_RBT));
        }

        const_reverse_iterator rend() const {
            return (const_reverse_iterator(_RBT.first, &_RBT));
        }
        
        //Capacity
        allocator_type get_allocator() const{
            return (_mallocator);
        }

        bool empty() const{
            if(_size == 0)
                return (true);
            else
                return (false);
        }

        size_type size() const{
            return (_size);
        }

        size_type max_size() const{
            return ((_nallocator.max_size()));
        }
        
        //Element access
        mapped_key &operator[](const Key &key){
            iterator itret;
            if ((itret = find(key)) != iterator(NULL, _RBT))
                return (itret->second);
            ft::pair<iterator, bool> ret = insert(ft::make_pair(key, mapped_key()));
            return (ret.first->second);
        }
        //Modifiers
        void clear(){
            erase(begin(), end());
        }

        void erase(iterator pos){
            //check if key exists
            iterator current = iterator(_RBT.first, &_RBT);
            if (_size == 1){
                _mallocator.destroy(current.base()->content);
                _nallocator.destroy(current.base());
                _mallocator.deallocate(current.base()->content, 1);
                _nallocator.deallocate(current.base(), 1);
                _size--;
                return ; 
            }
            iterator itleafs = iterator(_RBT.leafs, &_RBT);
            while (current != itleafs && current != pos)
                current++;
            //return 0 if key can't be found
            if (current == itleafs)
                return ;
            //current == key node
            ptrnode tmp1, tmp2;
            tmp1 = current.base();
            int tmp1_color = tmp1->color;
            //if node to delete has only a right child or no child
            if (current.base()->left == _RBT.leafs){
                tmp2 = current.base()->right;
                _RBT.transplant(current.base(), current.base()->right);
            }
            //if node to delete has only a left child
            else if (current.base()->right == _RBT.leafs){
                tmp2 = current.base()->left;
                _RBT.transplant(current.base(), current.base()->left);
            }
            //if node to delete has 2 children
            else{
                tmp1 = _RBT.find_min(current.base()->right);
                tmp1_color = tmp1->color;
                tmp2 = tmp1->right;
                if (tmp1->parent == current.base())
                    tmp2->parent = tmp1;
                else{
                    _RBT.transplant(tmp1, tmp1->right);
                    tmp1->right = current.base()->right;
                    tmp1->right->parent = tmp1;
                }
                _RBT.transplant(current.base(), tmp1);
                tmp1->left = current.base()->left;
                tmp1->left->parent = tmp1;
                tmp1->color = current.base()->color;
            }
            _mallocator.destroy(current.base()->content);
            _nallocator.destroy(current.base());
            _mallocator.deallocate(current.base()->content, 1);
            _nallocator.deallocate(current.base(), 1);
            if (tmp1_color == BLACK)
                check_rules_delete(tmp2);
            _size--;
            _RBT.first = _RBT.find_min(_RBT.root);
        }

        void erase(iterator first, iterator last){
            iterator tmp = first;
            while (first != last){
                tmp++;
                erase(first);
                first = tmp;
            }
        }

        size_type erase(const Key &key){
            //check if key exists
            ptrnode current = _RBT.root;
            if (_size == 1){
                _mallocator.destroy(current->content);
                _nallocator.destroy(current);
                _mallocator.deallocate(current->content, 1);
                _nallocator.deallocate(current, 1);
                _size--;
                return (1);
            }
            while (current != _RBT.leafs && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            //return 0 if key can't be found
            if (current == _RBT.leafs)
                return (0);
            //current == key node
            ptrnode tmp1, tmp2;
            tmp1 = current;
            int tmp1_color = tmp1->color;
            //if node to delete has only a right child or no child
            if (current->left == _RBT.leafs){
                tmp2 = current->right;
                _RBT.transplant(current, current->right);
            }
            //if node to delete has only a left child
            else if (current->right == _RBT.leafs){
                tmp2 = current->left;
                _RBT.transplant(current, current->left);
            }
            //if node to delete has 2 children
            else{
                tmp1 = _RBT.find_min(current->right);
                tmp1_color = tmp1->color;
                tmp2 = tmp1->right;
                if (tmp1->parent == current)
                    tmp2->parent = tmp1;
                else{
                    _RBT.transplant(tmp1, tmp1->right);
                    tmp1->right = current->right;
                    tmp1->right->parent = tmp1;
                }
                _RBT.transplant(current, tmp1);
                tmp1->left = current->left;
                tmp1->left->parent = tmp1;
                tmp1->color = current->color;
            }
            _mallocator.destroy(current->content);
            _nallocator.destroy(current);
            _mallocator.deallocate(current->content, 1);
            _nallocator.deallocate(current, 1);
            if (tmp1_color == BLACK)
                check_rules_delete(tmp2);
            _size--;
            _RBT.first = _RBT.find_min(_RBT.root);
            return (1);
        }
        /*-------------------------------------------------------
        insert function that insert a new element to the map
        val: value to insert (value_type)
        ---------------------------------------------------------*/
        pair<iterator, bool> insert(const value_type &val){
            //Allocate en set the new node
            node  def;
            ptrnode newnode = _nallocator.allocate(1);
            _nallocator.construct(newnode, def);
            newnode->right = _RBT.leafs;
            newnode->left = _RBT.leafs;
            ptrnode current = _RBT.root;
            ptrnode newnode_parent;
            newnode->content = _mallocator.allocate(1);
            _mallocator.construct(newnode->content, val);
            // if tree is empty insert as root
            if (_size == 0){
                _RBT.root = newnode;
                _RBT.first = newnode;
                _RBT.last = _RBT.leafs;
                _size++;
                return (ft::make_pair(begin(),true));
            }
            if (count(val.first) == 1)
                return (ft::make_pair(find(val.first), false));
            //Go throught the tree to find the place of the new key then insert it 
            while (current != _RBT.leafs){
                newnode_parent = current;
                if (_cmp(*newnode->content, *current->content))
                    current = current->left;
                else
                    current = current->right;
            }
            newnode->parent = newnode_parent;
            //set if newnode is at the left or right of its parent
            if (newnode_parent == _RBT.leafs)
                _RBT.root = newnode;
            if (_cmp(*newnode->content, *newnode_parent->content))
                newnode_parent->left = newnode;
            else
                newnode_parent->right = newnode;
            newnode->color = RED;
            _size++;
            //Check if rules aren't compromised and fix the tree if it's the case
            check_rules_insert(newnode);
            if (_cmp(*newnode->content, *_RBT.first->content))
                _RBT.first = newnode;
            return (ft::make_pair(iterator(newnode, &_RBT),true));
        }
        
        iterator insert(iterator hint, const value_type &value){
            (void)hint;
            pair<iterator, bool> ret;
            ret = insert(value);
            return(ret.first);
        }
        
        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            while (first != last){
                insert(*first);
                first++;
            }
        }

        void swap(map &other){
            Tree    tmp = other._RBT;
            other._RBT = this->_RBT;
            this->_RBT = tmp;
        }

        // //Lookup
        size_type count(const Key &key) const{
            if (find(key) != end())
                return (1);
            return (0);
        }

        iterator find(const Key &key){
            ptrnode current = _RBT.root;
            while (current != _RBT.leafs && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current != _RBT.leafs)
                return (iterator(current, &_RBT));
			return (end());
        }

        const_iterator find(const Key &key) const{
            ptrnode current = _RBT.root;
            while (current != _RBT.leafs && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current != _RBT.leafs)
                return (const_iterator(current, &_RBT));
			return (end());
        }

        ft::pair<iterator,iterator> equal_range(const Key &key){
            ft::pair<iterator, iterator>	ret;

			ret.first = lower_bound(key);
			ret.second = upper_bound(key);
			return (ret);
        }

        ft::pair<const_iterator,const_iterator> equal_range(const Key &key) const{
            ft::pair<iterator, iterator>	ret;

			ret.first = lower_bound(key);
			ret.second = upper_bound(key);
			return (ret);
        }

        iterator lower_bound(const Key &key){
            iterator it = begin();
            while (it != end()){
                if (!(key_comp(it->first, key)))
                    return (it);
                it++;
            }
            return (end());
        }

        const_iterator lower_bound(const Key &key) const{
            iterator it = begin();
            while (it != end()){
                if (!(key_comp(it->first, key)))
                    return (it);
                it++;
            }
            return (end());
        }

        iterator upper_bound(const Key &key){
            iterator it = begin();
            while (it != end()){
                if (!(key_comp(it->first, key)) && key_comp(key, it->first))
                    return (it);
                it++;
            }
            return (end());
        }

        const_iterator upper_bound(const Key &key) const{  
            iterator it = begin();
            while (it != end()){
                if (!(key_comp(it->first, key)) && key_comp(key, it->first))
                    return (it);
                it++;
            }
            return (end());
        }

        // //Observers
        protected:
        class value_compare : public std::binary_function<value_type, value_type, bool>{
        public:
            value_compare( Compare C):comp(C){}

            bool operator()(const value_type &lhs, const value_type &rhs) const {return (comp(lhs.first, rhs.first));}
        protected:
            key_compare comp;
        };

        key_compare key_comp() const{
            return(key_compare());
        }

        value_compare value_comp() const{
            return (value_compare(key_compare()));
        }

    private:
        //Map variables
        allocator_type      _mallocator;
        size_type           _size;
        value_compare       _cmp;
        Tree                _RBT;
        Nalloc              _nallocator;
    
        //check rules functions
        void    check_rules_insert(ptrnode newnode){
            ptrnode def;
            //If the newnode is the root or its direct children do nothing
            if (newnode->parent == NULL){
                newnode->color = BLACK;
                return ;
            }
            if (newnode->parent->parent == NULL)
                return ;
            //We don't want the parent of the newnode to be red so we make this while loop
            while (newnode->parent->color == RED){
                //if the newnode's parent is at the right of newnode's grandparent:
                //init def as the left of the newnode's grandparent
                if (newnode->parent == newnode->parent->parent->right){
                    def = newnode->parent->parent->left;
                    //if def != leaf && def->color is red
                    //newnode's parent and left of newnode's granparent become black
                    //newnode's grandparent become red, if it's the root it will be black
                    //newnode = its grandparent until we reach the root
                    if (def && def->color == RED){
                        def->color = BLACK;
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        newnode = newnode->parent->parent;
                    }
                    //rotation case
                    else{
                        if (newnode == newnode->parent->left){
                            newnode = newnode->parent;
                            _RBT.rotate_right(newnode);
                        }
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        _RBT.rotate_left(newnode->parent->parent);
                    }
                }
                else{
                    //reverse of the first if (if the right of the newnode's grandparent is red)
                    def = newnode->parent->parent->right;
                    if (def && def->color == RED){
                        def->color = BLACK;
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        newnode = newnode->parent->parent;
                    }
                    else{
                        if (newnode == newnode->parent->right){
                            newnode = newnode->parent;
                            _RBT.rotate_left(newnode);
                        }
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        _RBT.rotate_right(newnode->parent->parent);
                    }
                }
                if (newnode == _RBT.root)
                    break;
            }
            _RBT.root->color = BLACK;
        }
    
        void    check_rules_delete(ptrnode deletednode){
            ptrnode tmp;
            while (deletednode != _RBT.root && deletednode->color == BLACK){
                //if the deleted node is the left of its parent
                if (deletednode == deletednode->parent->left){
                    tmp = deletednode->parent->right;
                    if (tmp->color == RED){
                        tmp->color = BLACK;
                        deletednode->parent->color = RED;
                        _RBT.rotate_left(deletednode->parent);
                        tmp = deletednode->parent->right;
                    }
                    if (tmp->left->color == BLACK && tmp->right->color == BLACK){
                        tmp->color = RED;
                        deletednode = deletednode->parent;
                    }
                    else {
                        if (tmp->right->color == BLACK){
                            tmp->left->color = BLACK;
                            tmp->color = RED;
                            _RBT.rotate_right(tmp);
                            tmp = deletednode->parent->right;
                        }
                        tmp->color = deletednode->parent->color;
                        deletednode->parent->color = BLACK;
                        tmp->right->color = BLACK;
                        _RBT.rotate_left(deletednode->parent);
                        deletednode = _RBT.root;
                    }
                }
                //if the deleted node is the right of its parent
                else{
                    tmp = deletednode->parent->left;
                    if (tmp->color == RED){
                        tmp->color = BLACK;
                        deletednode->parent->color = RED;
                        _RBT.rotate_right(deletednode->parent);
                        tmp = deletednode->parent->left;
                    }
                    if (tmp->right->color == BLACK && tmp->right->color == BLACK){
                        tmp->color = RED;
                        deletednode = deletednode->parent;
                    }
                    else {
                        if (tmp->left->color == BLACK){
                            tmp->right->color = BLACK;
                            tmp->color = RED;
                            _RBT.rotate_left(tmp);
                            tmp = deletednode->parent->left;
                        }
                        tmp->color = deletednode->parent->color;
                        deletednode->parent->color = BLACK;
                        tmp->left->color = BLACK;
                        _RBT.rotate_right(deletednode->parent);
                        deletednode = _RBT.root;
                    }
                }
                deletednode->color = BLACK;
            }
        }
    };
}

#endif