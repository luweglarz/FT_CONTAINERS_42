#ifndef map_HPP
#define map_HPP

#include <iostream>
#include <memory>
#include <functional>
#include "utility/pair.hpp"
#include "../../iterators/map_iterator.hpp"
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
                    _RBT(){
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
                    _mallocator(alloc), _size(std::distance<InputIterator>(first, last)), _cmp(comp), _RBT(){}

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
            //erase(_RBT.root, _RBT.last);
        }
    
        //Iterators
        /*-------------------------------------------------------
        begin function that returns an iterator/const_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        iterator begin(){
            return (iterator(_RBT.first));
        }
        
        const_iterator begin() const{
            return (const_iterator(_RBT.first));
        }

        /*-------------------------------------------------------
        end function that returns an iterator/const_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        iterator end(){
            return (iterator(_RBT.last));
        }

        const_iterator end() const{
            return (const_iterator(_RBT.last));
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
            return ((_mallocator.max_size()));
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
            ptrnode current = _RBT.root;
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
            ptrnode tmp1, tmp2;
            tmp1 = current;
            int tmp1_color = tmp1->color;
            if (current->left == NULL){
                tmp2 = current->right;
                _RBT.transplant(current, current->right);
            }
            else if (current->right == NULL){
                tmp2 = current->left;
                _RBT.transplant(current, current->left);
            }
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
            _nallocator.destroy(current);
            if (tmp1_color == BLACK)
                check_rules_delete(tmp2);
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
                if (_cmp(val, *current->content))
                    current = current->left;
                else
                    current = current->right;
            }
            newnode->parent = newnode_parent;
            //set if newnode is at the left or right of its parent
            if (_cmp(*newnode->content, *newnode_parent->content))
                newnode->parent->left = newnode;
            else
                newnode->parent->right = newnode;
            newnode->color = RED;
            _size++;
            //Check if rules aren't compromised and fix the tree if it's the case
            check_rules_insert(newnode);
            if (_cmp(*newnode->content, *_RBT.first->content))
                _RBT.first = newnode;
            if (_cmp(*newnode->content, *_RBT.last->content))
                _RBT.last = newnode;
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
            ptrnode current = _RBT.root;
            while (current != NULL && current->content->first != key){
                if (key < current->content->first)
                    current = current->left;
                else
                    current = current->right;
            }
            if (current == _RBT.root && key != _RBT.root->content->first)
                return (iterator(NULL));
            return (iterator(current));
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
                        _RBT.rotate_left(newnode->parent->parent);
                    }
                }
                if (newnode == _RBT.root)
                    break;
            }
            _RBT.root->color = BLACK;
        }

        ptrnode delete_children(ptrnode current, int &key_color){
            ptrnode newChild;
            // if current has only left child
            if (current->left != NULL && current->right == NULL){
                newChild = current->left;
                key_color = current->color;
                if (current->parent == NULL)
                    _RBT.root = current->left;
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
                    _RBT.root = current->right;
                else
                    current->parent->right = newChild;
                newChild->parent = current->parent;
                return (current->right);
            }
            //if no children
            else {
                if (current->color == BLACK)
                    newChild = _nallocator.allocate(1);
                else
                    newChild = NULL;
                if (current->parent == NULL)
                    _RBT.root = newChild;
                else if (current->parent->left == current)
                    current->parent->left = newChild;
                else if (current->parent->right == current)
                    current->parent->right = newChild;
                std::cout << "newchild " << newChild->content->first <<std::endl;
                return (NULL);
            }
        }
    
        void    check_rules_delete(ptrnode deletednode){
            if (deletednode == _RBT.root)
                return ;
            ptrnode sibling = get_node_sibling(deletednode);
            if (sibling->color == RED){
                sibling->color = BLACK;
                deletednode->parent->color = RED;
                if (deletednode == deletednode->parent->left)
                    _RBT.rotate_left(deletednode->parent);
                else
                    _RBT.rotate_right(deletednode->parent);
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
                    _RBT.rotate_right(sibling);
                    sibling = deletednode->parent->right;
                }
                else if ((!deleted_left_child) && (sibling->left->color == BLACK || sibling->left == NULL)){
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    _RBT.rotate_left(sibling);
                    sibling = deletednode->parent->left;
                }
                sibling->color = deletednode->parent->color;
                deletednode->parent->color = BLACK;
                if (deletednode){
                    sibling->right->color = BLACK;
                    _RBT.rotate_left(deletednode->parent);
                }
                else{
                    sibling->left->color = BLACK;
                    _RBT.rotate_right(deletednode->parent);
                }
            }
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