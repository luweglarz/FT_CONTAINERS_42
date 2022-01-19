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
        val: the value that the container will be filled with 
        alloc: the allocator object
        ---------------------------------------------------------*/
        explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type &alloc = allocator_type()):
        _vallocator(alloc), _size(n), _capacity(n), _data(_vallocator.allocate(_capacity)){
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
        _vallocator(x._vallocator), _size(0), _capacity(0), _data(_vallocator.allocate(_capacity)){
            for (size_type i = 0; i > _size; i++){
                _vallocator.construct(&_data[i], x[i]);
            }
        }
        
        /*-------------------------------------------------------
        Assignation operator from x
        x: the copied instance
        ---------------------------------------------------------*/
        Vector &operator=(const Vector &x){
            _vallocator = x._vallocator;
            insert(begin(),x.begin(), x.end());
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
        rbegin function that returns a reverse_iterator of the end
        of the vector
        ---------------------------------------------------------*/
        reverse_iterator rbegin(){
            return (reverse_iterator(_data + _size - 1));
        }

        const_reverse_iterator rbegin() const {
            return (reverse_iterator(_data + _size - 1));
        }

        /*-------------------------------------------------------
        rend function that returns a reverse_iterator of the beginning
        of the vector
        ---------------------------------------------------------*/
        reverse_iterator rend(){
            reverse_iterator rev(_data - 1);
            return (rev);
        }

        const_reverse_iterator rend() const{
            reverse_iterator rev(_data - 1);
            return (rev);
        }

        //Capacity
        /*-------------------------------------------------------
        size function that returns the size of the vector
        ---------------------------------------------------------*/
        size_type size() const{
            return (_size);
        }

        /*-------------------------------------------------------
        max_size function that returns the maximum size that a vector
        can handle
        ---------------------------------------------------------*/
        size_type max_size() const{
            return (_vallocator.max_size()); 
        }

        /*-------------------------------------------------------
        resize function that change the size of the vector, if the new 
        new size is higher than the old size destroy the last (_size - n) elements
        n: new size of the vector
        val: the value that the vector will be filled with 
        ---------------------------------------------------------*/
        void    resize(size_type n, value_type val = value_type()){
            if (n < _size){
                while (_size != n){
                    _vallocator.destroy(&(_data[_size]));
                    _size--;
                }
            }
            else if (n > _size){
                if (n >= _capacity * 2)
                    reserve(n);
                while (_size < n)
                    push_back(val);
            }
        }

        /*-------------------------------------------------------
        capacity function that returns the _capacity of the vector
        (allocated memory)
        ---------------------------------------------------------*/
        size_type capacity() const{
            return (_capacity);
        }

        /*-------------------------------------------------------
        empty function that returns true whether the vector is empty
        and true if it is not
        ---------------------------------------------------------*/
        bool    empty() const{
            if (_size == 0)
                return (true);
            return (false);
        }

        /*-------------------------------------------------------
        reserve function that change the _capacity of the vector
        if n is higher that the _capacity .
        n: new _capacity of the vector
        val: the value that the vector will be filled with 
        ---------------------------------------------------------*/
        void    reserve(size_type n){
            if (n > max_size())
                throw std::length_error("ft::vector::reserve");
            if (n > _capacity){
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
        /*-------------------------------------------------------
        operator overload on [] that returns the element at n position
        n: position in the vector
        ---------------------------------------------------------*/
        reference operator[](size_type n){
            return (_data[n]);
        }

        const_reference operator[](size_type n) const{
            return (_data[n]);
        }

        /*-------------------------------------------------------
        at function that returns the element at n position
        n: position in the vector
        ---------------------------------------------------------*/
        reference at(size_type n){
            if (n >= _size)
                throw std::out_of_range("out of vector's range");
            return (_data[n]);
        }

        const_reference at(size_type n) const{
            if (n >= _size)
                throw std::out_of_range("out of vector's range");
            return (_data[n]);
        }

        /*-------------------------------------------------------
        front function that returns the first element of the vector
        ---------------------------------------------------------*/
        reference front(){
            return (*begin());
        }

        const_reference front() const{
            return (*begin());
        }

        /*-------------------------------------------------------
        back function that returns the last element of the vector
        ---------------------------------------------------------*/
        reference back(){
            return (*(--end()));
        }

        const_reference back() const{
            return (*(--end()));
        }

        //Modifiers
        /*-------------------------------------------------------
        assign function that remove all the elements of the vector
        and replace them with a range of element (first, last)
        first: first element of the iterator
        last: last element of the iterator
        ---------------------------------------------------------*/
        template <class InputIterator>
        void    assign(InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            clear();
            insert(begin(), first, last);
        }

        /*-------------------------------------------------------
        assign function that remove all the elements of the vector
        and replace with n elements of value val
        n: number of elements assigned
        val: value of the those elements
        ---------------------------------------------------------*/
        void    assign(size_type n, const value_type &val){
            clear();
            insert(begin(), n, val);
        }

        /*-------------------------------------------------------
        push_back function that push a new element to the end of 
        the vector
        val: value of the new element
        ---------------------------------------------------------*/
        void    push_back(const value_type &val){
            if (_capacity == 0){
                reserve(1);
                _vallocator.construct(&_data[0], val);
                _size = 1;
                return ;
            }
            if (_size >= _capacity)
                reserve(_capacity * 2);
            _vallocator.construct(&_data[_size], val);
            _size +=1;
        }

        /*-------------------------------------------------------
        pop_back function that remove the last element of the vector 
        ---------------------------------------------------------*/
        void    pop_back(){
            if (_size > 1)
                _size--;
        }

        /*-------------------------------------------------------
        insert function that insert a new element to vector at the
        specified position
        position: position where the new element is inserted
        val: value of the new element
        ---------------------------------------------------------*/
        iterator    insert(iterator position, const value_type &val){
            difference_type diff = &(*position) - &(*begin());
            iterator        insert_pos(begin() + diff);
            size_type       tmp_end;

            if (_size == 0)
                reserve(1);
            else if (_size >= _capacity)
                reserve(_capacity * 2);
            _size++;
            tmp_end = _size - 1;
            if (tmp_end != 0){
                while (tmp_end != static_cast<size_type>(diff)){
                    _vallocator.construct(&_data[tmp_end], _data[tmp_end - 1]);
                    tmp_end--;
                }
            }
            _data[tmp_end] = val;
            return (iterator(&_data[tmp_end]));
        }

        /*-------------------------------------------------------
        insert function that insert n new elements to vector at the
        specified position
        position: position where the new element is inserted
        n: number of new elements
        val: value of the new element
        ---------------------------------------------------------*/
        void    insert(iterator position, size_type n, const value_type &val){
            difference_type diff = std::distance(begin(), position);
            size_type new_size = n;

            if (_size == 0)
                reserve(n);
            else if (_size > _capacity)
                reserve(_capacity * 2);
            if (_size > 0){
                for (difference_type i = (_size - 1); i >= diff; i--)
                    _vallocator.construct(&_data[i + new_size], _data[i]);
            }
            for (size_type i = 0; i < n; i++){
                _vallocator.construct(&_data[diff], val);
                diff++;
            }
            _size += new_size;
        }

        /*-------------------------------------------------------
        insert function that insert the elements between (first, last)
        at position
        position: position where the new element is inserted
        first: first element of the iterator
        last: last element of the iterator
        ---------------------------------------------------------*/
        template <class InputIterator>
        void    insert(iterator position, InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            difference_type diff = std::distance(begin(), position);
            difference_type n = std::distance(first, last);
            size_type new_size = n;

            if (_size == 0)
                reserve(n);
            if (_size >= _capacity)
                reserve(_capacity * 2);
            if (_size > 0){
                for (difference_type i = (_size - 1); i >= diff; i--)
                    _vallocator.construct(&_data[i + new_size], _data[i]);
            }
            for (size_type i = 0; (difference_type)i < n; i++){
                _vallocator.construct(&_data[diff], *first);
                diff++;
                first++;
            }
            _size += new_size;
        }

        /*-------------------------------------------------------
        erase function that removes the element at position
        position: position of the element to remove
        ---------------------------------------------------------*/
        iterator erase(iterator position){
            iterator    b = begin();
            iterator    e = end();
            difference_type idx;
            value_type *store = NULL;
            store = _vallocator.allocate(_capacity);
            size_type i = 0;
            while (b != e){
                if (b == position){
                    idx = std::distance(begin(), b);
                    b++;
                }
                store[i] = *b;
                b++;
                i++;
            }
            iterator begin(&(store[0]));
            iterator end(&(store[i]));
            clear();
            _vallocator.deallocate(_data, _capacity);
            _data = store;
            _size = i;
            return (iterator(_data + idx));
        }

        /*-------------------------------------------------------
        erase function that removes the element between first and last
        first: first element of the iterator
        last: element of the iterator
        ---------------------------------------------------------*/
        iterator erase(iterator first, iterator last){
            iterator    b = begin();
            iterator    e = end();
            difference_type idx = _size - std::distance(begin(), first) - 1;
            value_type *store = NULL;
            store = _vallocator.allocate(_capacity);
            size_type i = 0;
            while (b != e){
                if (b == first)
                    while (first != last){
                        first++;
                        b++;
                    }
                store[i] = *b;
                b++;
                i++;
            }
            clear();
            _vallocator.deallocate(_data, _capacity);
            _data = store;
            _size = i;
            return (iterator(_data + idx));
        }

        /*-------------------------------------------------------
        swap function that swap the elements of *(this) with &x
        x: Vector to exchange the contents with
        ---------------------------------------------------------*/
        void    swap(Vector &x){
            allocator_type   tmp_allocator = _vallocator;
            size_type   tmp_size = _size;
            size_type   tmp_capacity = _capacity;

            _vallocator = x._vallocator;
            _size       = x._size;
            _capacity   = x._capacity;

            x._vallocator = tmp_allocator;
            x._size = tmp_size;
            x._capacity = tmp_capacity;
            std::swap(_data, x._data);
        }

        /*-------------------------------------------------------
        clear function that removes all the elements of the vector
        ---------------------------------------------------------*/
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
