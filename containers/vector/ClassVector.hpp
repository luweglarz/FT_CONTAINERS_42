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
        }

        /*-------------------------------------------------------
        constructor that creates a vector of size n
        n: initial size of the constructor
        val: the that you the container will be filled with 
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type &alloc = allocator_type()):
        _vallocator(alloc), _size(n), _capacity(n), _data(_vallocator.allocate(_size)){
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
        _vallocator(alloc), _size(std::distance<InputIterator>(first, last)), _capacity(_size), _data(_vallocator.allocate(_size)){
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
        Vector (const Vector& x):
        _vallocator(x._vallocator), _size(0), _capacity(0), _data(NULL){
            *this = x;
        }
        
        /*-------------------------------------------------------
        Assignation operator from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector &operator=(const Vector &x){
            _vallocator = x._vallocator;
            assign(x.begin(), x.end());
            return(*this);
        }
        /*-------------------------------------------------------
        Vector destructor
        ---------------------------------------------------------*/
        ~Vector(){
            for (size_type i = 0; i < _size; i++)
                _vallocator.destroy(&_data[i]);
            _vallocator.deallocate(_data, _capacity);
        }
        //Iterators:
        /*-------------------------------------------------------
        begin function that returns an iterator of the beginning
        of the vector
        ---------------------------------------------------------*/
        iterator begin(){
            return (iterator(_data));
        }

        const_iterator begin() const {
            return (iterator(_data));
        }

        /*-------------------------------------------------------
        end function that returns an iterator of the end
        of the vector (_size + 1)
        ---------------------------------------------------------*/
        iterator end(){
            return (iterator(_data + _size));
        }

        const_iterator end() const {
            return (iterator(_data + _size));
        }

        /*-------------------------------------------------------
        begin function that returns a reverse_iterator of the beginning
        of the vector
        ---------------------------------------------------------*/
        reverse_iterator rbegin(){
            return (reverse_iterator(_data + _size));
        }

        const_reverse_iterator rbegin() const {
            return (reverse_iterator(_data + _size));
        }

        /*-------------------------------------------------------
        end function that returns a reverse_iterator of the end
        of the vector
        ---------------------------------------------------------*/
        reverse_iterator rend(){
            return (reverse_iterator(_data));
        }

        const_reverse_iterator rend() const{
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
                    _vallocator.destroy(&(_data[_size]));
                    _size--;
                }
            }
            else if (n > _size && n <= _capacity){
                while (_size < n)
                    push_back(val);
            }
            else if (n > capacity()){
                reserve(n);
                while (_size < n)
                    push_back(val);
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
                throw std::length_error("ft::vector::reserve");
            else if (n > _capacity){
                value_type *store = NULL;
                store = _vallocator.allocate(n);
                size_type i = 0;
                while (i < _size){
                    _vallocator.construct(&store[i], _data[i]);
                    i++;
                }
                _vallocator.deallocate(_data, _capacity);
                _capacity = n;
                _data = store;
            }
        }
        //Element access
        
        reference operator[](size_type n){
            return (_data[n]);
        }

        const_reference operator[](size_type n) const{
            return (_data[n]);
        }

        reference at(size_type n){
            return (_data[n]);
        }

        const_reference at(size_type n) const{
            return (_data[n]);
        }

        reference front(){
            return (begin());
        }

        const_reference front() const{
            return (begin());
        }
        
        reference back(){
            return (end() - 1);
        }

        const_reference back() const{
            return (end() - 1);
        }

        //Modifiers
        template <class InputIterator>
        void    assign(InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            clear();
            _size = first - last ;
            if (_size > _capacity)
                _capacity = _size;
            _data = _vallocator.allocate(_size);
            int i = 0;
            std::cout << "first " << *first << std::endl;
            while (first != last){
                _vallocator.construct(&_data[i], *first);
                first++;
                i++;
            }
        }

        void    assign(size_type n, const value_type &val){
            clear();
            _size = n;
            if (_size > _capacity)
                _capacity = _size;
            _data = _vallocator.allocate(_capacity);
            for (size_type i = 0; i < _size; i++){
                _vallocator.construct(&_data[i], val);
            }
        }

        void    push_back(const value_type &val){
            if (_capacity == 0){
                _data = _vallocator.allocate(1);
                _vallocator.construct(&_data[0], val);
                _capacity = 1;
                _size = 1;
                return ;
            }
            if (_size >= _capacity)
                reserve(_capacity * 2);
            _vallocator.construct(&_data[_size], val);
            _size +=1;
        }

        void    pop_back(){
            resize(_size - 1);
        }

        iterator    insert(iterator position, const value_type &val){
            difference_type data_offset = &(*position) - &(*begin());
            std::cout << data_offset << std::endl;
            iterator    insert(begin() + data_offset);

            if (_size >= _capacity)
                reserve(_capacity * 2);
            _size += 1;
            if (insert != end())
                for (iterator it = end() - 1; it != insert; it--)
                    _vallocator.construct(&(*it), *(it - 1));
            _vallocator.construct(&(*insert), val);
            return (insert);
        }

        iterator    insert(iterator position, size_type n, const value_type &val){
            int i = 0;
            iterator ret = position;
            while (i < n){
                insert(position, val);
                position++;
                i++;
            }
            return(ret);
        }

        template <class InputIterator>
        iterator    insert(iterator position, InputIterator first, InputIterator last){
            iterator ret = position;
            while (first != last){
                insert(position, *first);
                first++;
            }
            return (ret);
        }

        iterator erase(iterator position){
            value_type  tmp_data;
            size_type   tmp_size = _size - 1;
            size_type   j = 0;
            for (size_type i = 0; i < tmp_size; i++){
                if (&(_data[j]) == position)
                    j++;
                tmp_data[i] = _data[j];
                j++;
            }
            clear();
            iterator begin(&(tmp_data[0]));
            iterator end(&(tmp_data[tmp_size]));
            assign(begin, end);
        }

        iterator erase(iterator first, iterator last){
            value_type  tmp_data;
            size_type   tmp_size = _size - 1;
            size_type   j = 0;
            for (size_type i = 0; i < tmp_size; i++){
                if (&(_data[j]) == first){
                    while (first != last){
                        first++;
                        j++;
                    }
                }
                tmp_data[i] = _data[j];
                j++;
            }
            clear();
            iterator begin(&(tmp_data[0]));
            iterator end(&(tmp_data[tmp_size]));
            assign(begin, end);
        }

        void    swap(Vector &x){
            std::swap<allocator_type>(_vallocator, x._vallocator);
            std::swap<size_type>(_size, x._size);
            std::swap<size_type>(_capacity, x._capacity);
            std::swap<value_type>(_data, x._data);
        }

        void    clear(){
            for (size_type i = 0; i < _size; i++){
                _vallocator.destroy(&(_data[i]));
            }
            _size = 0;
        }

    private:
        allocator_type  _vallocator;
        size_type       _size;
        size_type       _capacity;
        value_type      *_data;
    };

};

#endif
