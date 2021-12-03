#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>

namespace ft
{
    template <class T, class Alloc = std::allocator<T>>
    class Vector{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef T                                                  value_type;
        typedef Alloc                                              allocator_type;
        typedef T                                                  &reference;
        typedef const T                                            &const_reference;
        typedef T                                                  *pointer;
        typedef const T                                            *const_pointer;
        typedef std::iterator<std::random_access_iterator_tag, T>        iterator;
        typedef std::iterator<std::random_access_iterator_tag, const T>  const_iterator;
        typedef std::reverse_iterator<iterator>                     reverse_iterator;
        typedef std::reverse_iterator<const_iterator>               const_reverse_iterator;
        typedef ptrdiff_t                                           difference_type;
        typedef size_t                                              size_type;
        
        //Constructors:
        /*-------------------------------------------------------
        Default constructor that creates an empty vector
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(const allocator_type& alloc = allocator_type()){
        }

        /*-------------------------------------------------------
        constructor that creates a vector of size n
        n: initial size of the constructor
        val: the that you the container will be filled with 
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
            data = alloc.allocate(n);
            size = n;
            std::cout << "test" << std::endl;
            for (int i = 0; i < n; i++){
                data[i] = val;
                std::cout << "data " << data[i] << std::endl;
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
        template <class InputIterator>
        Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){
        }

        /*-------------------------------------------------------
        Copy constructor from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector (const Vector& x){
        }
        
    private:
        value_type  *data;
        size_type   size;
    };

};

#endif
