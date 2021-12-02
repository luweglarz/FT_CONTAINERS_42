#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft
{
    template <class T, class Alloc = std::allocator<T>>
    class Vector{
    public:
        typedef Alloc allocator_type;

        const T value_type;
        Alloc allocator_type;
        allocator_type reference;
        allocator_type const_reference;
        allocator_type pointer;
        allocator_type const_pointer;
        

        explicit Vector(const allocator_type& alloc = allocator_type()):data(alloc<T>.allocate(0)){
        }
        
    private:
        T   *data;
    };

}

#endif
