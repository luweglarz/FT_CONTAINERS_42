#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>
#include <limits>
#include "../../iterators/reverse_iterator.hpp"
#include "ClassIterators.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class Vector{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        // typedef typename means that we say to the compiler that it is a type from alloc
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
    
        typedef ft::vector_iterator<T>                              iterator;
        typedef ft::vector_iterator<const T>                        const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        typedef std::ptrdiff_t                                      difference_type;
        typedef size_t                                              size_type;
        
        //Constructors:
        /*-------------------------------------------------------
        Default constructor that creates an empty vector
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(const allocator_type &alloc = allocator_type()): _data(NULL), _vallocator(alloc), _size(0){
            std::cout << "Default constructor called" << std::endl;
        }

        /*-------------------------------------------------------
        constructor that creates a vector of size n
        n: initial size of the constructor
        val: the that you the container will be filled with 
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type &alloc = allocator_type()){
            std::cout << "Constructor with n and val called" << std::endl;
            _vallocator = alloc;
            _data = _vallocator.allocate(n);
            _size = n;
            for (int i = 0; i < n; i++){
                _data[i] = val;
                std::cout << "data " << _data[i] << std::endl;
            }
        }

        /*-------------------------------------------------------
        constructor that creates a vector between the range of first and last
        n: initial size of the constructor
        val: the that you the container will be filled with 
        alloc: the allocator object
        first: iterator that points on the first element of the range
        last: iterator that points on the last element of the range
        ---------------------------------------------------------*/
        template <typename InputIterator>
        Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){
            std::cout << "Range constuctor called" << std::endl;
            initialize_range(first,last,alloc);
        }

        /*-------------------------------------------------------
        Copy constructor from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector (const Vector& x){
            std::cout << "Copy constructor called" << std::endl;
        }

        //Iterators:
        /*-------------------------------------------------------
        begin function that returns an iterator of the beginning
        of the vector
        ---------------------------------------------------------*/
        iterator begin() const {
            return (iterator(_data));
        }


        /*-------------------------------------------------------
        end function that returns an iterator of the end
        of the vector (_size + 1)
        ---------------------------------------------------------*/
        iterator end() const {
            return (iterator(_data + _size));
        }

        /*-------------------------------------------------------
        begin function that returns a reverse_iterator of the beginning
        of the vector
        ---------------------------------------------------------*/
        reverse_iterator rbegin() const {
            return (reverse_iterator(_data + _size));
        }

        /*-------------------------------------------------------
        end function that returns a reverse_iterator of the end
        of the vector
        ---------------------------------------------------------*/
        reverse_iterator rend() const {
            return (reverse_iterator(_data));
        }

    protected:
        //Initializators for range constructor
        /*-------------------------------------------------------
        Used initializator if parameters are integrals instead of
        iterators
        ---------------------------------------------------------*/
        void initialize_range(size_type n, value_type val, const allocator_type &alloc){
            std::cout << "initialize n val" << std::endl;
            _vallocator = alloc;
            _data = _vallocator.allocate(n);
            _size = n;
            for (unsigned int i = 0; i < n; i++){
                _data[i] = val;
                std::cout << "data " << _data[i] << std::endl;
            }
        }

        /*-------------------------------------------------------
        Used initializator if parameters are iterators
        ---------------------------------------------------------*/
        void initialize_range(iterator n, iterator val, const allocator_type &alloc){
            std::cout << "initialize it" << std::endl;
        }

    private:
        value_type      *_data;
        allocator_type  _vallocator;
        size_type       _size;
    };

};

#endif
