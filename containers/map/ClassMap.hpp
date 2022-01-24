#ifndef MAP_HPP
#define MAP_HPP

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
	class Map{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef Key                                                 key_type;
        typedef T                                                   mapped_key;
        typedef ft::pair<const Key, T>                              value_type;
        typedef size_t                                              size_type;
        typedef ptrdiff_t                                           difference_type;
        typedef Compare                                             key_compare;
        typedef Alloc                                               allocator_type;

        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

        typedef ft::map_iterator<T>                                 iterator;
        typedef ft::map_iterator<const T>                           const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;

        //Constructors
        /*-------------------------------------------------------
        Default constructor that creates an empty map
        comp: comparator object
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Map(const Compare &comp, const allocator_type &alloc = allocator_type()): _mallocator(alloc), _size(0), _cmp(comp), 
                    _first(NULL), _last(NULL), _current(NULL){
        }

        /*-------------------------------------------------------
        fill constructor that creates a map with a range of iterators
        first: iterator that points on the first element of the range
        last: iterator that points on the last element of the range
        comp: comparator object
        alloc: the allocator object
        ---------------------------------------------------------*/
        template <class InputIterator>
        explicit Map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
                    _mallocator(alloc), _size(std::distance<InputIterator>(first, last)), _cmp(comp){}

        /*-------------------------------------------------------
        copy constructor that creates a map with a range of iterators
        x: source map object to copy
        ---------------------------------------------------------*/
        Map(const Map &x){
            *this = x;
        }

        Map &operator=(const Map &x){
            (void)x;
        }

        ~Map(){
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
            return (iterator(_first));
        }

        /*-------------------------------------------------------
        end function that returns an iterator/const_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        iterator end(){
            return (iterator(_last));
        }

        const_iterator end() const{
            return (iterator(_last));
        }

        /*-------------------------------------------------------
        rbegin function that returns a reverse_iterator/const_reverse_iterator 
        at the beginning of the map
        ---------------------------------------------------------*/
        reverse_iterator rbegin(){
            return (iterator(_first));
        }

        const_reverse_iterator rbegin() const{
            return (iterator(_first));
        }

        /*-------------------------------------------------------
        rend function that returns a reverse_iterator/const_reverse_iterator 
        at the end of the map
        ---------------------------------------------------------*/
        reverse_iterator rend(){
            return (iterator(_last));
        }

        const_reverse_iterator rend() const {
            return (iterator(_last));
        }

    protected:
        class value_compare : public std::binary_function<value_type, value_type, bool>{
        public:
            value_compare( Compare C):comp(C){}

            bool operator()(const value_type &lhs, const value_type &rhs) const {return (comp(lhs.first, rhs.first));}
        protected:
            Compare comp;
        };

    private:
        typedef RBTNode<value_type>        node;

        allocator_type      _mallocator;
        size_type           _size;
        value_compare       _cmp;
        node                *_first;
        node                *_current;
        node                *_last;
    };
}

#endif