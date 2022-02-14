#ifndef map_HPP
#define map_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "utility/pair.hpp"
#include "../../iterators/map_iterator.hpp"
#include "../../iterators/map_reverse_iterator.hpp"
#include "utility/StructRBT.hpp"

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
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;

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
            return (iterator(_RBT.first, _RBT));
        }
        
        const_iterator begin() const{
            return (const_iterator(_RBT.first, _RBT));
        }

        /*-------------------------------------------------------
        end function that returns an iterator/const_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        iterator end(){
            return (iterator(_RBT.last, _RBT));
        }

        const_iterator end() const{
            return (const_iterator(_RBT.last, _RBT));
        }

        /*-------------------------------------------------------
        rbegin function that returns a reverse_iterator/const_reverse_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        reverse_iterator rbegin(){
            return (reverse_iterator(_RBT.last));
        }

        const_reverse_iterator rbegin() const{
            return (const_reverse_iterator(_RBT.last));
        }

        /*-------------------------------------------------------
        rend function that returns a reverse_iterator/const_reverse_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        reverse_iterator rend(){
            return (reverse_iterator(_RBT.first));
        }

        const_reverse_iterator rend() const {
            return (const_reverse_iterator(_RBT.first));
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
            erase(pos->first);
        }

        void erase(iterator first, iterator last){
            iterator tmp = first;
            while (first != last){
                std::cout << "begin " << _RBT.first->content->first << std::endl;
                tmp++;
                erase(first->first);
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
                return (1);
            }
            while (current != NULL && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            //return 0 if key can't be found
            if (current == NULL)
                return (0);
            //current == key node
            ptrnode tmp1 = NULL, tmp2 = NULL;
            node    def;
            tmp1 = current;
            int tmp1_color = tmp1->color;
            //if node to delete has only a right child or no child
            bool children = true;
            if (current->left == NULL){
                if (current->right == NULL){
                    current->right = _nallocator.allocate(1);
                    _nallocator.construct(current->right, def);
                    children = false;
                }
                tmp2 = current->right;
                _RBT.transplant(current, current->right);
            }
            //if node to delete has only a left child
            else if (current->right == NULL){
                tmp2 = current->left;
                _RBT.transplant(current, current->left);
            }
            //if node to delete has 2 children
            else{
                tmp1 = _RBT.find_min(current->right);
                tmp1_color = tmp1->color;
                tmp1->right = _nallocator.allocate(1);
                _nallocator.construct(tmp1->right, def);
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
           // std::cout << "tmp2 " << tmp2->content->first << std::endl;
            if (tmp1_color == BLACK)
                check_rules_delete(tmp2, children);
            _size--;
            _RBT.first = _RBT.find_min(_RBT.root);
            _RBT.last = _RBT.find_max(_RBT.root);
            return (1);
        }
        /*-------------------------------------------------------
        insert function that insert a new element to the map
        val: value to insert (value_type)
        ---------------------------------------------------------*/
        pair<iterator, bool> insert(const value_type &val){
            node  def;
            ptrnode newnode = _nallocator.allocate(1);
            ptrnode current = _RBT.root;
            ptrnode newnode_parent;

            _nallocator.construct(newnode, def);
            newnode->content = _mallocator.allocate(1);
            _mallocator.construct(newnode->content, val);
            // if tree is empty insert as root
            if (_size == 0){
                _RBT.root = newnode;
                _RBT.first = newnode;
                _RBT.last = newnode;
                _size++;
                return (ft::make_pair(begin(),true));
            }
            //Go throught the tree to find the place of the new key then insert it 
            while (current != NULL){
                newnode_parent = current;
                if (_cmp(*newnode->content, *current->content))
                    current = current->left;
                else
                    current = current->right;
            }
            newnode->parent = newnode_parent;
            //set if newnode is at the left or right of its parent
            if (newnode_parent == NULL)
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
            if (_cmp(*_RBT.last->content, *newnode->content))
                _RBT.last = newnode;
            return (ft::make_pair(iterator(newnode, _RBT),true));
        }
        
        // iterator insert(iterator hint, const value_type &value){
        //     (void)hint;
        //     (void)value;
        //     return;
        // }
        
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
            iterator it = find(key);
            if (it != iterator(NULL, _RBT))
                return (1);
            return (0);
        }

        iterator find(const Key &key){
            ptrnode current = _RBT.root;
            while (current != NULL && current->content->first != key){
                //std::cout << "current: " << current->content->first << std::endl;
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
                //std::cout << "current2: " << current->content->first << std::endl;
            }
            if (current == _RBT.root && key != _RBT.root->content->first)
                return (iterator(NULL, _RBT));
            return (iterator(current, _RBT));
        }

        const_iterator find(const Key &key) const{
            ptrnode current = _RBT.root;
            while (current != NULL && current->content->first != key){
                if (_cmp(key, current->content->first))
                    current = current->left;
                else
                    current = current->right;
            }
            if (current == _RBT.root && key != _RBT.root->content->first)
                return (const_iterator(NULL, _RBT));
            return (const_iterator(current, _RBT));
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
    
        void    check_rules_delete(ptrnode deletednode, bool children){
            ptrnode tmp;
            while (deletednode != _RBT.root && deletednode->color == BLACK){
                //if the deleted node is the left of its parent
                (void)children;
                if (deletednode == deletednode->parent->left){
                    //std::cout << "deletednode " << deletednode->content->first << std::endl;
                    tmp = deletednode->parent->right;

                    std::cout << "deleted " << deletednode->parent->content->first << std::endl;
                    //std::cout << "parent " << deletednode->parent->right->content->first << std::endl;
                    if (tmp->color == RED){
                        std::cout << "red\n";
                        tmp->color = BLACK;
                        deletednode->parent->color = RED;
                        _RBT.rotate_left(deletednode->parent);
                        tmp = deletednode->parent->right;
                    }
                    if ((tmp->left == NULL || tmp->left->color == BLACK) && tmp->right->color == BLACK){
                        tmp->color = RED;
                        deletednode->parent->left = NULL;
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
                        std::cout << "deleted " << deletednode->parent->content->first << std::endl;
                        if (deletednode->parent == _RBT.root){
                            std::cout << "test\n";
                            _RBT.root->left = NULL;
                        }
                        if (children == false){
                            deletednode->parent->left = NULL;
                            deletednode->parent->right = NULL;
                        }
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
                    if ((tmp->right == NULL || tmp->right->color == BLACK) && tmp->right->color == BLACK){
                        tmp->color = RED;
                        deletednode->parent->right = NULL;
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
                        if (deletednode->parent == _RBT.root)
                            _RBT.root->right = NULL;
                        if (children == false){
                            deletednode->parent->left = NULL;
                            deletednode->parent->right = NULL;
                        }
                        deletednode = _RBT.root;
                    }
                }
                deletednode->color = BLACK;
            }
        }
    };
}

#endif