#ifndef map_HPP
#define map_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "utility/pair.hpp"
#include "../../iterators/map_iterator.hpp"
#include "utility/StructRBTNode.hpp"

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
        typedef RBTNode<value_type>                                 node;
        typedef typename std::allocator<node>                       nalloc;
        typedef node                                                *ptrnode;
    public:
        typedef ft::map_iterator<node>                              iterator;
        typedef ft::map_iterator<const node>                        const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;

        //Constructors
        /*-------------------------------------------------------
        Default constructor that creates an empty map
        comp: comparator object
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit map(const Compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _mallocator(alloc), _size(0), _cmp(comp), 
                    _root(NULL), _first(NULL), _last(NULL){
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
                    _mallocator(alloc), _size(std::distance<InputIterator>(first, last)), _cmp(comp){}

        /*-------------------------------------------------------
        copy constructor that creates a map with a range of iterators
        x: source map object to copy
        ---------------------------------------------------------*/
        map(const map &x){
            *this = x;
        }

        map &operator=(const map &x){
            (void)x;
        }

        ~map(){
            //erase(_root, _last);
        }
    
        //Iterators
        /*-------------------------------------------------------
        begin function that returns an iterator/const_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        iterator begin(){
            return (iterator(_first));
        }
        
        const_iterator begin() const{
            return (const_iterator(_first));
        }

        /*-------------------------------------------------------
        end function that returns an iterator/const_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        iterator end(){
            return (iterator(_last));
        }

        const_iterator end() const{
            return (const_iterator(_last));
        }

        /*-------------------------------------------------------
        rbegin function that returns a reverse_iterator/const_reverse_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        reverse_iterator rbegin(){
            return (reverse_iterator(_last));
        }

        const_reverse_iterator rbegin() const{
            return (const_reverse_iterator(_last));
        }

        /*-------------------------------------------------------
        rend function that returns a reverse_iterator/const_reverse_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        reverse_iterator rend(){
            return (reverse_iterator(_first));
        }

        const_reverse_iterator rend() const {
            return (const_reverse_iterator(_first));
        }
        
        //Capacity
        allocator_type get_allocator() const{
            return (_nallocator);
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
        T &at(const Key &key){
            iterator    ret = find(key);
            return (ret->second);
        }

        T &operator[](const Key &key){
            iterator    ret = find(key);
            return (ret->second);
        }
        //Modifiers
        // void clear(){
        // }

        // void erase(iterator pos){
        //     (void)pos;
        // }

        // void erase(iterator first, iterator last){
        //     (void)first;
        //     (void)last;
        // }

        size_type erase(const Key &key){
            //check if key exists
            ptrnode current = _root;
            while (current != NULL && current->content.first != key){
                if (key < current->content.first)
                    current = current->left;
                else
                    current = current->right;
            }
            //return 0 if key can't be found
            if (current == NULL)
                return (0);
            //current == key node
            ptrnode fixing_node;
            int key_color;
            //if current has two children
            if (current->left != NULL && current->right !=NULL){
                ptrnode order_fix = find_mini(current->right);
                //gotta make current->content a pointer on content so we can assign even if one of the value is const
                current->content = order_fix->content;
                fixing_node = delete_children(order_fix, key_color);
            }
            //if has 0 or one children
            else
                fixing_node = delete_children(current, key_color);
            if (key_color == BLACK){
                check_rules_delete(fixing_node);
            }
            return (1);
        }
        /*-------------------------------------------------------
        insert function that insert a new element to the map
        val: value to insert (value_type)
        ---------------------------------------------------------*/
        pair<iterator, bool> insert(const value_type &val){
            node  def;
            ptrnode newnode = _nallocator.allocate(1);
            ptrnode current = _root;
            ptrnode newnode_parent;

            _nallocator.construct(newnode, def);
            _mallocator.construct(&newnode->content, val);
            // if tree is empty insert as root
            if (_size == 0){
                _root = newnode;
                _first = newnode;
                _last = newnode;
                _size++;
                return (ft::make_pair(begin(),true));
            }
            //Go throught the tree to find the place of the new key then insert it 
            while (current != NULL){
                newnode_parent = current;
                if (_cmp(val, current->content))
                    current = current->left;
                else
                    current = current->right;
            }
            newnode->parent = newnode_parent;
            //set if newnode is at the left or right of its parent
            if (_cmp(newnode->content, newnode_parent->content))
                newnode->parent->left = newnode;
            else
                newnode->parent->right = newnode;
            newnode->color = RED;
            _size++;
            //Check if rules aren't compromised and fix the tree if it's the case
            check_rules_insert(newnode);
            if (_cmp(newnode->content, _first->content))
                _first = newnode;
            if (_cmp(newnode->content, _last->content))
                _last = newnode;
            return (ft::make_pair(iterator(newnode),true));
        }
        
        // iterator insert(iterator hint, const value_type &value){
        //     (void)hint;
        //     (void)value;
        //     return;
        // }
        
        // template<class InputIterator>
        // void insert(InputIterator first, InputIterator last){
        //     (void)first;
        //     (void)last;
            
        // }

        // void swap(map &other){
        //     (void)other;
        // }

        // //Lookup
        // size_type count(const Key &key) const{
        //     (void)key;
        //     return;
        // }

        iterator find(const Key &key){
            ptrnode current = _root;
            while (current != NULL && current->content.first != key){
                if (key < current->content.first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current == _root && key != _root->content.first)
                return (iterator(NULL));
            return (iterator(current));
        }

        const_iterator find(const Key &key) const{
            ptrnode current = _root;
            while (current != NULL && current->content.first != key){
                if (_cmp(key, current->content.first))
                    current = current->left;
                else
                    current = current->right;
            }
            if (current == _root && key != _root->content.first)
                return (const_iterator(NULL));
            return (const_iterator(current));
        }

        // ft::pair<iterator,iterator> equal_range(const Key &key){
        //     (void)key;
        //     return;
        // }

        // ft::pair<const_iterator,const_iterator> equal_range(const Key &key) const{
        //     (void)key;
        //     return;
        // }

        // iterator lower_bound(const Key &key){
        //     (void)key;
        //     return;
        // }

        // const_iterator lower_bound(const Key &key) const{
        //     (void)key;
        //     return;
        // }

        // iterator upper_bound(const Key &key){
        //     (void)key;
        //     return;
        // }

        // const_iterator upper_bound(const Key &key) const{  
        //     (void)key;
        //     return;
        // }

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
        nalloc              _nallocator;
        allocator_type      _mallocator;
        size_type           _size;
        value_compare       _cmp;
        ptrnode             _root;
        ptrnode             _first;
        ptrnode             _last;

        //Red Black Tree functions

        void    rotate_left(ptrnode rot){
            ptrnode right = rot->right;
            rot->right = right->left;
            if (right->left != NULL)
                right->left->parent = rot;
            right->parent = rot->parent;
            if (rot->parent == NULL)
                _root = right;
            else if (rot == rot->parent->left)
                rot->parent->left = right;
            else
                rot->parent->right = right;
            right->left = rot;
            rot->parent = right;
        }

        void    rotate_right(ptrnode rot){
            ptrnode left = rot->left;
            rot->left = left->right;
            if (left->right != NULL)
                left->right->parent = rot;
            left->parent = rot->parent;
            if (rot->parent == NULL)
                _root = left;
            else if (rot == rot->parent->right)
                rot->parent->right = left;
            else
                rot->parent->left = left;
            left->right = rot;
            rot->parent = left;
        }

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
                            rotate_right(newnode);
                        }
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        rotate_left(newnode->parent->parent);
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
                            rotate_left(newnode);
                        }
                        newnode->parent->color = BLACK;
                        newnode->parent->parent->color = RED;
                        rotate_left(newnode->parent->parent);
                    }
                }
                if (newnode == _root)
                    break;
            }
            _root->color = BLACK;
        }

        ptrnode delete_children(ptrnode current, int &key_color){
            ptrnode newChild;
            // if current has only left child
            if (current->left != NULL && current->right == NULL){
                newChild = current->left;
                key_color = current->color;
                if (current->parent == NULL)
                    _root = current->left;
                else
                    current->parent->left = newChild;
                newChild->parent = current->parent;
                return (current->left);
            }
            //if current has only right child
            else if (current->right != NULL && current->left == NULL){
                newChild = current->right;
                key_color = current->color;
                if (current->parent == NULL)
                    _root = current->right;
                else
                    current->parent->right = newChild;
                newChild->parent = current->parent;
                return (current->right);
            }
            //if no children
            else {
                return (NULL);
            }
        }
    
        void    check_rules_delete(ptrnode deletednode){
            if (deletednode == _root)
                return ;
            ptrnode sibling = get_node_sibling(deletednode);
            if (sibling->color == RED){
                sibling->color = BLACK;
                deletednode->parent->color = RED;
                if (deletednode == deletednode->parent->left)
                    rotate_left(deletednode->parent);
                else
                    rotate_right(deletednode->parent);
                sibling = get_node_sibling(deletednode);
            }
            if ((sibling->left->color == BLACK || sibling->left == NULL) &&
                (sibling->left->color == BLACK || sibling->left == NULL)){
                if (deletednode->parent->color == RED)    
                    sibling->color = BLACK;
                else
                    check_rules_delete(deletednode->parent);
            }
            else{
                bool deleted_left_child = false;
                if (deletednode == deletednode->parent->left)
                    deleted_left_child = true;
                if ((deleted_left_child) && (sibling->right->color == BLACK || sibling->right == NULL)){
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotate_right(sibling);
                    sibling = deletednode->parent->right;
                }
                else if ((!deleted_left_child) && (sibling->left->color == BLACK || sibling->left == NULL)){
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotate_left(sibling);
                    sibling = deletednode->parent->left;
                }
                sibling->color = deletednode->parent->color;
                deletednode->parent->color = BLACK;
                if (deletednode){
                    sibling->right->color = BLACK;
                    rotate_left(deletednode->parent);
                }
                else{
                    sibling->left->color = BLACK;
                    rotate_right(deletednode->parent);
                }
            }
        }
        ptrnode find_mini(ptrnode right){
            while (right->left != NULL)
                right = right->left;
            return (right);
        }
        ptrnode    get_node_sibling(ptrnode node){
            if (node == node->parent->left)
                return (node->parent->right);
            else if (node == node->parent->right)
                return (node->parent->left);
            return (NULL);
        }
    };
}

#endif