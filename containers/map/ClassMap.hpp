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
        typedef RBTNode<value_type>                                 node;
        typedef std::allocator<node>                                Nalloc;

        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

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
                    _root(NULL), _current(NULL), _last(NULL){
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
            return (iterator(_root));
        }
        
        const_iterator begin() const{
            return (const_iterator(_root));
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
            return (reverse_iterator(_root));
        }

        const_reverse_iterator rend() const {
            return (const_reverse_iterator(_root));
        }
        
        //Capacity
        allocator_type get_allocator() const{
            return (_mallocator);
        }

        bool empty() const{
            return true;
        }

        size_type size() const{
            return 0;
        }

        size_type max_size() const{
            return 0;
        }
        //Element access
        // T &at(const Key &key){
        //     (void)key;
        //     return;
        // }

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

        // size_type erase(const Key &key){
        //     (void)key;
        //     return;
        // }
        /*-------------------------------------------------------
        insert function that insert a new element to the map
        val: value to insert (value_type)
        ---------------------------------------------------------*/
        pair<iterator, bool> insert(const value_type &val){
            node  *newnode;
            if (_size == 0){
                newnode = _nallocator.allocate(1);
                _mallocator.construct(&newnode->content, val);
                _root = newnode;
                _size++;
                return (ft::make_pair(begin(),true));
            }

            return (ft::make_pair(begin(),true));
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
            _current = _root;
            while (_current != NULL && _current->content.first != key){
                if (key < _current->content.first)
                    _current = _current->left;
                else
                    _current = _current->right;
            }
            return (iterator(_current));
        }

        const_iterator find(const Key &key) const{
            _current = _root;
            while (_current != NULL && _current->content.first != key){
                if (_cmp(key, _current->content.first))
                    _current = _current->left;
                else
                    _current = _current->right;
            }
            return (iterator(_current));
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
        // key_compare key_comp() const{
        //     return;
        // }

        // ft::map::value_compare value_comp() const{
        //     return;
        // }
        
    protected:
        class value_compare : public std::binary_function<value_type, value_type, bool>{
        public:
            value_compare( Compare C):comp(C){}

            bool operator()(const value_type &lhs, const value_type &rhs) const {return (comp(lhs.first, rhs.first));}
        protected:
            Compare comp;
        };

    private:
        Nalloc              _nallocator;
        allocator_type      _mallocator;
        size_type           _size;
        value_compare       _cmp;
        node                *_root;
        node                *_current;
        node                *_last;
    };
}

#endif