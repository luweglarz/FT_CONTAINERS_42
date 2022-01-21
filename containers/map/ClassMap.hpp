#ifndef MAP_HPP
#define MAP_HPP

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
        explicit Map( const Compare &comp, const allocator_type &alloc = allocator_type()): _mallocator(alloc), _size(0), _cmp(comp), current(NULL){
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
        allocator_type      _mallocator;
        size_type           _size;
        value_compare       _cmp;
        RBTN<value_type>    *current;
    };
}

#endif