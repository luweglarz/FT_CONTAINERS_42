#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>
#include <limits>

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class Vector{
    public:
        /*-------------------------------------------------------
        Defining types with typedef
        ---------------------------------------------------------*/
        typedef T                                                  value_type;
        typedef Alloc                                              allocator_type;
        // allocator_type is dependant on Alloc which is a dynamic type so we need to add typename
        typedef typename allocator_type::reference                          reference;
        typedef typename allocator_type::const_reference                    const_reference;
        typedef typename allocator_type::pointer                            pointer;
        typedef typename allocator_type::const_pointer                      const_pointer;
    
        typedef std::iterator<std::random_access_iterator_tag, T>        iterator;
        typedef std::iterator<std::random_access_iterator_tag, const T>  const_iterator;
        typedef std::reverse_iterator<iterator>                     reverse_iterator;
        typedef std::reverse_iterator<const_iterator>               const_reverse_iterator;
        typedef std::ptrdiff_t                                           difference_type;
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
            if(std::numeric_limits<InputIterator>::is_integer)
            {
                std::cout << "Range constuctor called with an integral" << std::endl;
                size_type n = static_cast<size_type>(first);
                value_type &val = static_cast<value_type>(last);
                _vallocator = alloc;
                _data = _vallocator.allocate(n);
                _size = n;
                for (int i = 0; i < n; i++){
                    _data[i] = val;
                    std::cout << "data " << _data[i] << std::endl;
                }
                return ;
            }
            int i = 0;
            while (first != last){
                _data[i] = dynamic_cast<T>(*first.pointer);
                i++;
                first++;
            }
            std::cout << "Range constuctor called" << std::endl;
        }

        /*-------------------------------------------------------
        Copy constructor from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector (const Vector& x){
            std::cout << "Copy constructor called" << std::endl;
        }
        
    private:
        value_type      *_data;
        allocator_type  _vallocator;
        size_type       _size;
    };

};

#endif
