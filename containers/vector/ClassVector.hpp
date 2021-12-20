#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <iterator>
#include <limits>
#include <stdexcept>
#include "../../iterators/reverse_iterator.hpp"
#include "../../iterators/vector_iterator.hpp"
#include "../../SFINAE/enable_if.hpp"
#include "../../SFINAE/is_integral.hpp"

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
        explicit Vector(const allocator_type &alloc = allocator_type()): _vallocator(alloc), _size(0),_capacity(0), _data(NULL){
            std::cout << "Default constructor called" << std::endl;
        }

        /*-------------------------------------------------------
        constructor that creates a vector of size n
        n: initial size of the constructor
        val: the that you the container will be filled with 
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type &alloc = allocator_type()):
        _vallocator(alloc), _size(n), _capacity(n), _data(_vallocator.allocate(_size)){
            std::cout << "Constructor with n and val called" << std::endl;
            for (size_type i = 0; i < n; i++){
                _vallocator.construct(&_data[i], val);
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
        //  template <typename InputIterator>
        // Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        // typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
        // (void)alloc;
        // (void)first;
        // (void)last;
        // }

        template <typename InputIterator>
        Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
        _vallocator(alloc), _size(std::distance<InputIterator>(first, last)), _data(_vallocator.allocate(_size)){
            std::cout << "Range constuctor called" << std::endl;
            int i = 0;
            while (first != last){
                _data[i] = *first;
                first++;
            }
        }

        /*-------------------------------------------------------
        Copy constructor from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector (const Vector& x){
            std::cout << "Copy constructor called" << std::endl;
            *this = x;
        }
        
        /*-------------------------------------------------------
        Assignation operator from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector &operator=(const Vector &x){
            _vallocator = x._vallocator;
            _size = x._size;
            for (size_type i; i < _size; i++){
                _data[i] = x._data;
            }
            return(*this);
        }
        /*-------------------------------------------------------
        Vector destructor
        ---------------------------------------------------------*/
        ~Vector(){
            _vallocator.deallocate(_data, _capacity);
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
        reverse_iterator rend() const{
            return (reverse_iterator(_data));
        }

        size_type size() const{
            return (_size);
        }

        size_type max_size() const{
            return (_vallocator.max_size()); 
        }

        //capacity
        void    resize(size_type n, value_type val = value_type()){
            if (n < _size){
                while (_size != n){
                    _vallocator.destroy(_data[_size]);
                    _size--;
                }
            }
            else if (n > _size){
            }
            else if (n > capacity()){

            }
        }

        size_type capacity() const{
            return (_capacity);
        }

        bool    empty() const{
            if (_size == 0)
                return (true);
            return (false);
        }

        void    reserve(size_type n){
            if (n > max_size())
                throw std::length_error();
            else if (n > _capacity){
                value_type store = _data;
                _vallocator.deallocate(_data, _capacity);
                _capacity = n;
                _vallocator.allocate(n);
                _data = store;
            }
        }
        //Modifiers
        template <class InputIterator>
        void    assign(InputIterator first, InputIterator last){
            _vallocator.deallocate(_data, _capacity);
            _size = std::distance(first, last);
            _capacity = _size;
            _data = _vallocator.allocate(_size);
            for (size_type i; i < _size; i++){
                _vallocator.construct(&_data[i], *first);
                first++;
            }
        }

        void    assign(size_type n, const value_type &val){
            _vallocator.deallocate(_data, _capacity);
            _size = n;
            _capacity = _size;
            _data = _vallocator.allocate(_size);
            for (size_type i; i < _size; i++){
                _vallocator.construct(&_data[i], val);
            }
        }

        void push_back(const value_type &val){
            if (_size == _capacity)
                _capacity *= 2;
            
        }

    private:
        allocator_type  _vallocator;
        size_type       _size;
        size_type       _capacity;
        value_type      *_data;
    };

};

#endif
