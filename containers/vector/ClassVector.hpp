#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include <limits>
#include <stdexcept>
#include "../../iterators/vector_reverse_iterator.hpp"
#include "../../iterators/vector_iterator.hpp"
#include "../../SFINAE/enable_if.hpp"
#include "../../SFINAE/is_integral.hpp"
#include "../../iterators/lexicographical_compare.hpp"

namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector{
    public:
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

        explicit vector(const allocator_type &alloc = allocator_type()): _vallocator(alloc), _size(0),_capacity(0), _data(NULL){
        }

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type &alloc = allocator_type()):
        _vallocator(alloc), _size(n), _capacity(n), _data(_vallocator.allocate(_capacity)){
            for (size_type i = 0; i < n; i++){
                _vallocator.construct(&_data[i], val);
            }
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
        _vallocator(alloc), _size(std::distance<InputIterator>(first, last)), _capacity(_size), _data(_vallocator.allocate(_capacity)){
            int i = 0;
            while (first != last){
                _vallocator.construct(&_data[i], *first);
                first++;
                i++;
            }
        }

        vector (const vector& x):
        _vallocator(x._vallocator), _size(0), _capacity(0){
            *this = x;
        }
        
        vector &operator=(const vector &x){
            _vallocator = x._vallocator;
            _size = x._size;
            _capacity = x._capacity;
            _data = _vallocator.allocate(_capacity);
            for (size_type i = 0; i < _size;i++){
                _vallocator.construct(&_data[i], x._data[i]);
            }
            return(*this);
        }

        ~vector(){
            for (size_type i = 0; i < _size; i++)
                _vallocator.destroy(&_data[i]);
            _vallocator.deallocate(_data, _capacity);
        }

        iterator begin(){
            return (iterator(_data));
        }

        const_iterator begin() const {
            return (const_iterator(_data));
        }

        iterator end(){
            return (iterator(_data + _size));
        }

        const_iterator end() const {
            return (const_iterator(_data + _size));
        }

        reverse_iterator rbegin(){
            return (reverse_iterator(_data + _size));
        }

        const_reverse_iterator rbegin() const {
            return (const_reverse_iterator(_data + _size));
        }

        reverse_iterator rend(){
            return (reverse_iterator(_data));
        }

        const_reverse_iterator rend() const{
            return (const_reverse_iterator(_data));
        }

        size_type size() const{
            return (_size);
        }

        size_type max_size() const{
            return (_vallocator.max_size()); 
        }

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

        reference front(){
            return (*begin());
        }

        const_reference front() const{
            return (*begin());
        }

        reference back(){
            return (*(--end()));
        }

        const_reference back() const{
            return (*(--end()));
        }

        template <class InputIterator>
        void    assign(InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            clear();
            insert(begin(), first, last);
        }

        void    assign(size_type n, const value_type &val){
            clear();
            insert(begin(), n, val);
        }

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

        void    pop_back(){
            if (_size > 0)
                _size--;
        }

        iterator    insert(iterator position, const value_type &val){
            difference_type diff = std::distance(begin(), position);
            iterator        insert_pos(begin() + diff);
            size_type       tmp_end;

            if (_size == 0)
                reserve(1);
            else if (_size >= _capacity)
                reserve(_capacity * 2);
            tmp_end = _size;
            if (tmp_end != 0){
                while (tmp_end != static_cast<size_type>(diff)){
                    _vallocator.construct(&_data[tmp_end], _data[tmp_end - 1]);
                    tmp_end--;
                }
            }
            _data[tmp_end] = val;
            _size++;
            return (iterator(&_data[tmp_end]));
        }
    
        void    insert(iterator position, size_type n, const value_type &val){
            difference_type diff = std::distance(begin(), position);
            size_type new_size = n;

            if (_size + n > _capacity && _size + n <= _capacity * 2)
                reserve(_capacity * 2);
            else if (_size + n > _capacity * 2)
                reserve(_size + n);
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

        template <class InputIterator>
        void    insert(iterator position, InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0){
            difference_type diff = std::distance(begin(), position);
            difference_type n = std::distance(first, last);
            size_type new_size = n;

            if (_size + n > _capacity && _size + n <= _capacity * 2)
                reserve(_capacity * 2);
            else if (_size + n > _capacity * 2)
                reserve(_size + n);
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

        iterator erase(iterator position){
            return (erase(position, position + 1));
        }

        iterator erase(iterator first, iterator last){
            iterator    b = begin();
            value_type *store = NULL;
            store = _vallocator.allocate(_capacity);
            size_type i = 0;
            size_type idx = first - begin();
            
            if (first != last){
                while (b != end()){
                    if (b == first)
                        while (first != last){
                            first++;
                            b++;
                        }
                    if (b == end())
                        break;
                    store[i] = *b;
                    b++;
                    i++;
                }
            }
            clear();
            _vallocator.deallocate(_data, _capacity);
            _data = store;
            _size = i;
            return (begin() + idx);
        }

        void    swap(vector &x){
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

        void    clear(){
            for (size_type i = 0; i < _size; i++){
                _vallocator.destroy(&(_data[i]));
            }
            _size = 0;
        }

        allocator_type  get_allocator() const{
            return (_vallocator);
        }
    private:
        allocator_type  _vallocator;
        size_type       _size;
        size_type       _capacity;
        value_type      *_data;
    };

    template<class T, class Alloc>
    void    swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs){
        lhs.swap(rhs);
    }

    template <class T, class Alloc>
    bool operator==(const ft::vector<T, Alloc> &lhs,
                    const ft::vector<T, Alloc> &rhs){
        typename ft::vector<T>::const_iterator b1 = lhs.begin();
        typename ft::vector<T>::const_iterator e1 = lhs.end();
        typename ft::vector<T>::const_iterator b2 = rhs.begin();
        typename ft::vector<T>::const_iterator e2 = rhs.end();
        if (lhs.size() == rhs.size() && lhs.capacity() == rhs.capacity()){
            while (b1 != e1 && b2 != e2){
                if (*b1 != *b2)
                    return (false);
                b1++;
                b2++;
            }
            return (true);
        }
        return (false);
    }
    template <class T, class Alloc>
    bool operator!=(const ft::vector<T, Alloc> &lhs,
                    const ft::vector<T, Alloc> &rhs){
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<(const ft::vector<T, Alloc> &lhs,
                    const ft::vector<T, Alloc> &rhs){
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));                
    }
    template <class T, class Alloc>
    bool operator<=(const ft::vector<T, Alloc> &lhs,
                    const ft::vector<T, Alloc> &rhs){
        return (!(rhs < lhs));              
    }
    template <class T, class Alloc>
    bool operator>(const ft::vector<T, Alloc> &lhs,
                    const ft::vector<T, Alloc> &rhs){
        return (rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>=(const ft::vector<T, Alloc> &lhs,
                    const ft::vector<T, Alloc> &rhs){
        return (!(lhs < rhs));           
    }
};

#endif
